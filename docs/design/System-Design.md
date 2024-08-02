# System Design

<!--toc:start-->

- [System Design](#system-design)
  - [Key Components](#key-components)

The hexapod robot software architecture aims to be modular, scalable, and maintainable.
The architecture is designed to be cross-platform, ensuring that the same design principles can
be applied regardless of the specific hardware platform used.

## Key Components

1. Platform Abstraction Layer (PAL)/BSP
2. Inter-Core Communication (ICC) Layer
3. Hardware Abstraction Layer (HAL)
4. Core Modules
5. Application Layer

![System Design](./SoftwareDesign.png)

The design leverages a dual asymetric processing setup, where one core runs Linux and handles high-level processing
and sensor data acquisition (DAQ), while the other core runs FreeRTOS and manages low-level servo control.
This design separates high-level processing tasks from low-level real-time tasks. From a hardware perspective, it is flexible
as to how this can be implemented. We could have two seperate chips: a Microprocessor and a Microcontroller which communicate
via a external interface. Another setup is instead have both cores on the same SoC.

- **Core A (Linux Core):**
  Handles high-level processing, sensor data acquisition (DAQ), and overall control logic.
  Communicates with the MCU core to delegate real-time tasks.
- **Core B (MCU Core):**
  Handles low-level servo control and real-time operations.
  Receives commands from the Linux core and sends status updates back.
