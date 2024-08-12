#!/usr/bin/env python
import pandas as pd
import matplotlib.pyplot as plt
import sys

def plot_xyz_from_csv(filename):
    # Step 1: Load the CSV file
    df = pd.read_csv(filename)

    # Step 2: Extract x, y, z coordinates
    x = df['x']
    y = df['y']
    z = df['z']

    # Set reasonable bounds for the y-axis (m/s^2)
    y_min, y_max = -7, 7  # Adjust these limits as necessary
    y_min_zaxis, y_max_zaxis = -5, 12  # Adjust these limits as necessary

    # Step 3: Create separate plots for x, y, and z
    plt.figure(figsize=(15, 5))

    # Plot for X
    plt.subplot(1, 3, 1)
    plt.plot(x, marker='o', linestyle='-', color='r')
    plt.ylim(y_min, y_max)
    plt.title('X Coordinate')
    plt.xlabel('Index')
    plt.ylabel('Acceleration (m/s²)')

    # Plot for Y
    plt.subplot(1, 3, 2)
    plt.plot(y, marker='o', linestyle='-', color='g')
    plt.ylim(y_min, y_max)
    plt.title('Y Coordinate')
    plt.xlabel('Index')
    plt.ylabel('Acceleration (m/s²)')

    # Plot for Z
    plt.subplot(1, 3, 3)
    plt.plot(z, marker='o', linestyle='-', color='b')
    plt.ylim(y_min_zaxis, y_max_zaxis)
    plt.title('Z Coordinate')
    plt.xlabel('Index')
    plt.ylabel('Acceleration (m/s²)')

    # Step 4: Adjust layout and show the plots
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <filename>")
    else:
        plot_xyz_from_csv(sys.argv[1])
