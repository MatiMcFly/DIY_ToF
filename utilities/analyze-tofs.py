import numpy as np
import matplotlib.pyplot as plt

# Load data from logs.txt
filename = 'logs.txt'
data = np.loadtxt(filename, delimiter=';', dtype=float)

# Calculate arithmetic mean and standard deviation for each column
means = np.mean(data, axis=0)
std_devs = np.std(data, axis=0)

# Print results
for i, (mean, std_dev) in enumerate(zip(means, std_devs), start=1):
    print(f"Column {i}: Mean = {mean:.2f}, Standard Deviation = {std_dev:.2f}")

# Plot all columns with points
plt.figure(figsize=(10, 6))
labels = ["0 m", "1 m", "2 m", "4 m", "6 m", "7 m"]
for i in range(data.shape[1]):
    plt.scatter(range(len(data[:, i])), data[:, i], label=labels[i], s=5)

plt.title('ToF for different cable lengths')
plt.xlabel('Index')
plt.ylabel('ToF [ps]')
plt.legend()
plt.grid()
plt.tight_layout()
plt.show()
