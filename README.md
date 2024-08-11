# Miles Hexapod Robot - Software

<!--toc:start-->

- [Miles Hexapod Robot - Software](#miles-hexapod-robot-software)
  - [Repository Structure](#repository-structure)
  - [Getting Started](#getting-started)
    - [Dependencies](#dependencies)
    - [Compiling](#compiling)
  - [Porting to other Platforms](#porting-to-other-platforms)
  - [Contribution Guidelines](#contribution-guidelines)
  - [License](#license)
  <!--toc:end-->

This repository contains the software and OS images for the Miles hexapod robot project.
The software is designed with modularity at its core principle, allowing for
devices to be added with ease.

The primary target hardware is the Milk-V Duo SBC, but despite this, heavy emphasis
is put on making a portable design, enabling you to adapt it for other platforms
with minimal effort.

The repository is divided into two main components:

1. **Software:** The software stack is responsible for controlling the robot’s movement,
   processing sensor data, and making decisions based on the environment.
   It is structured to be highly modular, allowing for easy integration of new
   sensors, actuators, and processing algorithms.
2. **OS Images:** Custom OS images are provided to ensure that the underlying operating
   system contains neccesary packages, overylays, and drivers for the robot software
   to run on the platform. These images are tailored for the Milk-V Duo SBC but
   can be adapted to other platforms. buildroot is used to create these images.

The software is divided into several key layers:

- **Platform Abstraction Layer (PAL):** This layer abstracts hardware-specific details,
  providing a consistent API for interacting with the platform’s GPIO, SPI, I2C,
  and other peripherals.
- **Hardware Abstraction Layer (HAL):** The HAL provides an additional level of abstraction,
  focusing on higher-level hardware components such as sensors and actuators.
  It builds on the PAL to provide device-specific interfaces that are platform-independent.
- **Core Modules:** The core modules are responsible for the main functionalities
  and control logic of the system. These modules handle tasks such as movement control,
  sensor data processing,
- **Application Layer:** The topmost layer of the software stack. It coordinates
  the core modules to perform tasks and respond to user commands, as well as expose
  itself to the outside world via dashboards and telemetry. Behavioural algorithms
  are implemented here. User interfaces for interaction and control are exposed here.

More detail about system architecture can be found in the [Design Document](docs/design/System-Design.md)

## Repository Structure

```txt
Miles-SW/
├── include/                 # Header files
│   ├── common/              # Common code
│   ├── drivers/             # Device drivers (used by HAL)
│   ├── pal/                 # Platform Abstraction Layer (PAL)
│   ├── hal/                 # Hardware Abstraction Layer (HAL)
│   └── application/         # Application Layer
├── src/                     # Source files
│   ├── common/              # Common code implementations
│   ├── drivers/             # Device drivers implementations (used by HAL)
│   ├── pal/                 # PAL implementations
│   ├── hal/                 # HAL implementations
│   └── application/         # Application logic
├── build_project.sh         # Build script that runs within the SW container.
├── duo-buildroot-sdk/       # Milk-V Duo Buildroot to build OS images
├── tests/                   # Unit tests for all layers
├── build/                   # Build artifacts (generated after building)
├── Dockerfile               # Dockerfile for building the software with RISC-V toolchain
├── CMakeLists.txt           # CMake configuration for SW
├── Makefile                 # Makefile for building OS images and software
└── README.md                # This file

```

## Getting Started

### Dependencies

- **git:** Version control to clone the repository
- **docker:** Required for building the software using the provided Docker environment.
- **make:** Build management
- **CMake:** Build system on host

### Compiling

The build system is entirely containerized. You can build the hexapod software
within a Docker container that includes the RISC-V toolchain.

The OS images for the hexapod robot can be built using the provided Docker environment.

To build everything in their respective containers, just run

```sh
make # Builds everything
```

You can the compiled software in `build/sw`, if tests are enabled then those
can be found in `build/sw/tests`.
The output of the OS build can be found in `build/os`

OS images and software can be built seperately.

```sh
make software # Builds software
make os # Builds OS Images
```

You can flash OS images to an SD card with

```sh
sudo dd if=build/os/out/<image name>.img of=/dev/<sd device> bs=4M status=progress
```

## Porting to other Platforms

The hexapod software is designed to be easily ported to other platforms. The Platform
Abstraction Layer (PAL) isolates platform-specific code, allowing you to implement
the necessary interfaces (e.g., SPI, GPIO) for your target hardware. For most
platforms, majority of the PAL will be untouched as the PAL utilized kernel subsystems,
and device-tree overlays will get bundled for each platform as part of its PAL.

There may be scenarios where kernel subsystems can't be used, in that case implementers
must use platform platform-specific code.

The PAL can also target other OS'es or bare metal if need be.

To port the software:

1. **Implement the PAL for Your Platform:** Write the platform-specific implementations
   for SPI, GPIO, etc.
2. **Update Build Configurations:** Modify the build scripts (e.g., CMakeLists.txt,
   Makefile) to include your platform-specific code.
3. **Test and Validate:** Run the unit tests to ensure that the software behaves
   correctly on your target platform.

## Contribution Guidelines

Contributions are welcome! Do be mindful that the main target platform is the Milk-V,
as such contributions for this platform will get more attention. Features can be
requested on [Github Issues](https://github.com/AeybelV/Miles-SW/issues) and
assigned a ticket number. There is a git commit hook that checks if commit messages
contain GH ticket numbers (ie. SW-#4), although this is succeptible to change
depending on project traction. The project tries to be "formal" in how progress
is dealt. Features or bugs are creates via Github issues, and dedicated branches
with commits referencing the issue ticket are made. Most project tracking is centralized
and kept within Github Issues and Github Projects, so the project isn't really "fork"
friendly at the moment, but this can change.

If you want to contribute to the project, please follow these steps:

1. Fork the repository.
2. Create a new branch `git checkout -b SW<#>-feature`, where # is the GH issue number.
3. Make your changes.
4. Commit your changes `git commit -m 'SW-#<issue numer>: some feature'`.
5. Push to the branch `git push origin  SW<#>-feature`.
6. Open a Pull Request.

Please ensure your code adheres to the project's coding standards (WIP) and includes
relevant unit tests.

## License

This project is licensed under the GNU General Public License v3.0 License.
See the [LICENSE](LICENSE) file for details.
