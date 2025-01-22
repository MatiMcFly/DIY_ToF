import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.ticker as mticker
from collections import deque
import re

# Configuration
COM_PORT    = 'COMX'
BAUD_RATE   = 38400
MAX_SAMPLES = 20000

# Calibration (zero point)
TOF_0M_PS = 25800 # ToF at cable length 0m in [ps]

# Constants
TOF_MIN_PS       = 0                      # ToF min. value (sanity check) [ps]
TOF_MAX_PS       = 30000 + TOF_0M_PS      # ToF max. value (sanity check) [ps]
TOF_PS_TO_LEN_CM = 0.9 * 3e8 / 1e12 * 100 # from [ps] to [cm] via c

def parse_tof(line):
    """Extract the ToF value from a line of text."""
    match = re.search(r'ToF\s*=\s*(\d+)\s*\[ps\]', line)
    if match:
        return int(match.group(1))
    return None

def update(frame):
    """Update the plot with new data."""
    global data, ser

    try:
        if ser.in_waiting > 0:
            lines = ser.read(ser.in_waiting).decode('utf-8').splitlines()
            for line_content in lines:
                tof_value = parse_tof(line_content)
                if tof_value is not None and tof_value > TOF_MIN_PS and tof_value < TOF_MAX_PS:  # Skip invalid values
                    tof_value -= TOF_0M_PS  # Calibration
                    data.append(tof_value)

                    # Print latest value
                    tof_str_ps = f"{tof_value:,.0f}".replace(",", "'")  # 1000th separator
                    tof_cm     = round(tof_value * TOF_PS_TO_LEN_CM)        # No decimal places
                    line_text.set_text(f"Latest ToF: {tof_str_ps} ps | {tof_cm} cm")

        # Update the Line2D object
        line.set_data(range(len(data)), data)
        ax.relim()
        ax.autoscale_view()
    except Exception as e:
        print(f"Error reading from serial port: {e}")

# Initialize serial port
try:
    ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {COM_PORT} at {BAUD_RATE} baud.")
except Exception as e:
    print(f"Failed to connect to serial port: {e}")
    exit()

# Initialize plot
fig, ax = plt.subplots()
data = deque(maxlen=MAX_SAMPLES)  # Increase buffer to hold up to 2000 samples
line, = ax.plot([], [], label="ToF [ps]")  # Create a Line2D object
ax.set_ylabel("Time of Flight [ps]")
ax.set_xlabel("Index")
plt.gca().yaxis.set_major_formatter(mticker.FuncFormatter(lambda x, _: f"{x:,.0f}".replace(",", "'")))

ax_m = ax.twinx()  # Create secondary y-axis
ax_m.set_ylabel("Cable Length [cm]")  # Label for secondary y-axis

line_text = plt.text(0.5, 0.95, "", transform=plt.gca().transAxes, ha="center")

def update_secondary_yaxis_limits(*args):
    """Update the secondary y-axis limits whenever the primary y-axis changes."""
    primary_limits = ax.get_ylim()
    ax_m.set_ylim(primary_limits[0] * TOF_PS_TO_LEN_CM, primary_limits[1] * TOF_PS_TO_LEN_CM)

# Connect the limit update to the primary y-axis changes
ax.callbacks.connect("ylim_changed", update_secondary_yaxis_limits)

# Initial call to synchronize the limits
update_secondary_yaxis_limits()

ani = animation.FuncAnimation(fig, update, interval=50)

# Show plot
try:
    plt.show()
except KeyboardInterrupt:
    print("Exiting...")
finally:
    ser.close()
