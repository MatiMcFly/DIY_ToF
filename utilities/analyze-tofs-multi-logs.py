import matplotlib.pyplot as plt
import matplotlib.ticker as mticker
import numpy as np

# Function to read ToF values from a log file
def read_tof_values(filename):
    tof_values = []
    with open(filename, 'r') as file:
        for line in file:
            if "ToF =" in line:
                try:
                    value = int(line.split('=')[1].split()[0])
                    tof_values.append(value)
                except (IndexError, ValueError):
                    print(f"Skipping malformed line in {filename}: {line.strip()}")
    return tof_values

# Read ToF values from the three log files
log_files = ["log1.txt", "log2.txt", "log3.txt"]
datasets = []

for log_file in log_files:
    datasets.append(read_tof_values(log_file))

# Combine all data for plotting and calculate indices
data_indices = []
offset = 0

for data in datasets:
    indices = list(range(offset, offset + len(data)))
    data_indices.append(indices)
    offset += len(data)

# Plot the data
plt.figure(figsize=(10, 6))
colors = ['blue', 'orange', 'green']  # Colors for the datasets
labels = ['19 cm', '24 cm', '29 cm']  # Dataset labels

for i, (indices, data) in enumerate(zip(data_indices, datasets)):
    # Scatter plot for the original data points
    plt.scatter(indices, data, label=f'Distanz = {labels[i]}', color=colors[i], s=10)

    # Add mean value as a horizontal line within the range of the dataset
    mean_value = np.mean(data)
    plt.plot(indices, [mean_value] * len(indices), color=colors[i], linestyle='--', linewidth=2, label=f'Distanz = {labels[i]} (Mean)')

    # Linear fit for the dataset (polynomial of degree 1, i.e., a straight line)
    slope, intercept = np.polyfit(indices, data, 1)  # Fit a line to the data
    fit_line = np.polyval([slope, intercept], indices)  # Calculate the fitted values
    plt.plot(indices, fit_line, color=colors[i], linestyle=':', linewidth=2, label=f'Distanz = {labels[i]} (Linear Fit)')

# Customize the plot
plt.title('ToF unterschiedliche Distanzen zum Spiegel')
plt.xlabel('Index')
plt.ylabel('ToF [ps]')
plt.gca().yaxis.set_major_formatter(mticker.FuncFormatter(lambda x, _: f"{x:,.0f}".replace(",", "'")))
plt.legend()
plt.grid(True)

# Show the plot
plt.show()
