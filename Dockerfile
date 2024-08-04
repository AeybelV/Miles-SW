# Use an official Ubuntu as a parent image
FROM ubuntu:22.04

# Set environment variables for non-interactive installation
ENV DEBIAN_FRONTEND=noninteractive

# Install required dependencies
RUN apt-get update && apt-get install -y \
    autoconf \
    automake \
    autotools-dev \
    bc \
    bison \
    build-essential \
    cmake \
    curl \
    flex \
    gawk \
    git \
    gperf \
    libexpat-dev \
    libgmp-dev \
    libglib2.0-dev \
    libmpc-dev \
    libmpfr-dev \
    libslirp-dev \
    libtool \
    ninja-build \
    patchutils \
    python3 \
    python3-pip \
    texinfo \
    wget \
    zlib1g-dev

# Clone the RISC-V GNU Toolchain repository
RUN git clone https://github.com/riscv/riscv-gnu-toolchain /opt/riscv-gnu-toolchain

# Build the RISC-V toolchain for RV64 for linux targets
WORKDIR /opt/riscv-gnu-toolchain
RUN ./configure --prefix=/opt/riscv
RUN make linux -j$(nproc)

# Add the toolchain to the PATH
ENV PATH=/opt/riscv/bin:$PATH

# Copy the project into the Docker image
COPY . /opt/miles

# Set the working directory to your project
WORKDIR /opt/miles

# Setups CMake
RUN cmake -S . -B build/sw

# Copy the build script into the Docker image
COPY build_project.sh /usr/local/bin/build_project.sh
RUN chmod +x /usr/local/bin/build_project.sh

# Set the entrypoint to a shell, allows for running commands if needed
ENTRYPOINT ["/bin/bash"]

