# Miles Robot Hardware Overview

This document provides an overview of the various hardware components used on
Mile hexapod robot project. Each section describes a specific device,
its purpose, and how it interacts within the software.

## Milk-V Duo SBC

The Milk-V Duo Single Board Computer (SBC) is the main processing unit
of the hexapod robot. It runs the operating system and handles high-level
processing tasks, such as sensor data acquisition, path planning, and control algorithms.

- **Processor:** Dual-core RISC-V processor.
  - **C906:** RV64 big core that runs at 1GHz. Runs Linux and the software stack
  - **C906:** RV64 "little" core that runs at 700Mhz, acts as a MCU.
- **Connectivity:** Includes USB, GPIO, SPI, I2C, and UART interfaces for connecting
  peripherals.
- **Operating System:** The hexapod robot’s software runs on a custom Linux image.

## Servo Motor Drivers

### Description

Servo motors are used to control the movement of the hexapod’s legs. Each leg typically
has three servo motors, allowing for precise control of leg position and movement.

Each servo motor requires a PWM signal. Due to the number of motors, a Servo driver
(PWM driver) is used.

## IMU (Inertial Measurement Unit)

The IMU is a sensor that provides orientation, acceleration, and angular velocity
data. It helps the hexapod maintain balance and orientation while moving.
Typically includes a 3-axis accelerometer, gyroscope, and sometimes a magnetometer.

The IMU data is processed by the software to adjust the hexapod’s movement and maintain
stability. It is accessed via the Hardware Abstraction Layer (HAL).

## Camera Module

The camera module is used for vision-based tasks. Connected via CSI, USB, or similar
interfaces. The camera feed is processed by the software for tasks like obstacle
recognition or navigation. Advanced image processing algorithms may be employed.

## 2D LiDAR Sensor (Optional)

The 2D LiDAR sensor provides precise distance measurements by emitting laser pulses
and measuring the time it takes for the reflection to return. It is used for
mapping and navigation. LiDAR data is used for tasks like SLAM
(Simultaneous Localization and Mapping) and obstacle avoidance. The sensor
data is processed to build a map of the robot’s surroundings.

## Additional Sensors

Additional sensors and modules can be added to the hexapod robot to extend its
capabilities. These may include temperature sensors, infrared sensors, or other
specialized modules.
