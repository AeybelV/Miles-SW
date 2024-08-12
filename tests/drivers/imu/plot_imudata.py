#!/usr/bin/env python
import pandas as pd
import matplotlib.pyplot as plt
import sys

# Set reasonable bounds for the y-axis
# accelerometer limits
y_min_acc, y_max_acc = -50, 50
y_min_z_acc, y_max_z_acc = -15, 30
# gyroscope limits
y_min_gyro, y_max_gyro = -20, 20
y_min_z_gyro, y_max_z_gyro = -20, 20
# marker size
mrkr_size = 1


def plot_xyz_from_csv(filename, y_title, y_min, y_max, y_min_zaxis, y_max_zaxis):
    # Load the CSV file
    df = pd.read_csv(filename)

    # Extract x, y, z coordinates
    x = df["x"]
    y = df["y"]
    z = df["z"]

    # Create separate plots for x, y, and z
    plt.figure(figsize=(15, 5))

    # Plot for X
    plt.subplot(1, 3, 1)
    plt.plot(x, marker="o", linestyle="-", color="r", markersize=mrkr_size)
    plt.ylim(y_min, y_max)
    plt.title("X Coordinate")
    plt.xlabel("Index")
    plt.ylabel(y_title)

    # Plot for Y
    plt.subplot(1, 3, 2)
    plt.plot(y, marker="o", linestyle="-", color="g", markersize=mrkr_size)
    plt.ylim(y_min, y_max)
    plt.title("Y Coordinate")
    plt.xlabel("Index")
    plt.ylabel(y_title)

    # Plot for Z
    plt.subplot(1, 3, 3)
    plt.plot(z, marker="o", linestyle="-", color="b", markersize=mrkr_size)
    plt.ylim(y_min_zaxis, y_max_zaxis)
    plt.title("Z Coordinate")
    plt.xlabel("Index")
    plt.ylabel(y_title)

    # Step 4: Adjust layout and show the plots
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python script.py <acc|gyro> <filename>")
    else:
        if sys.argv[1] == "acc":
            plot_xyz_from_csv(
                sys.argv[2],
                "Linear Acceleration (m/s²)",
                y_min_acc,
                y_max_acc,
                y_min_z_acc,
                y_max_z_acc,
            )
        elif sys.argv[1] == "gyro":
            plot_xyz_from_csv(
                sys.argv[2],
                "Angular Acceleration (rad/s²)",
                y_min_gyro,
                y_max_gyro,
                y_min_z_gyro,
                y_max_z_gyro,
            )
        else:
            plot_xyz_from_csv(
                sys.argv[2], "Value", y_min_acc, y_max_acc, y_min_z_acc, y_max_acc
            )
