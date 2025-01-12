import numpy as np
import matplotlib.pyplot as plt

# Read the data from the log.txt file
with open('log.txt', 'r') as file:
    tof_values = []
    for line in file:
        # Extract the ToF value using the pattern 'ToF = <value> [ps]'
        if 'ToF' in line:
            tof_value = int(line.split('=')[1].split('[')[0].strip())
            tof_values.append(tof_value)

# Convert the list to a numpy array for easier calculation
tof_array = np.array(tof_values)

# Calculate the arithmetic mean and standard deviation
mean_tof = np.mean(tof_array)
std_tof = np.std(tof_array)

# Print the results
print(f'Arithmetic Mean of ToF: {mean_tof}')
print(f'Standard Deviation of ToF: {std_tof}')

# Plot a histogram
plt.figure(figsize=(10, 6))
plt.hist(tof_array, bins=20, color='skyblue', edgecolor='black', alpha=0.7)
plt.title('Histogram of ToF Values')
plt.xlabel('Time-of-Flight (ps)')
plt.ylabel('Frequency')
plt.grid(True)
plt.show()

# Plot a box plot
plt.figure(figsize=(10, 6))
plt.boxplot(tof_array, vert=False, patch_artist=True, boxprops=dict(facecolor='lightblue', color='black'))
plt.title('Box Plot of ToF Values')
plt.xlabel('Time-of-Flight (ps)')
plt.grid(True)
plt.show()
