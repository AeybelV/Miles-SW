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
    cmake-curses-gui \
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
    rsync \
    texinfo \
    wget \
    zlib1g-dev

# =========================== RISC-V Toolchain ===========================
# Clone the RISC-V GNU Toolchain repository
# RUN git clone https://github.com/riscv/riscv-gnu-toolchain /opt/riscv-gnu-toolchain

# Build the RISC-V toolchain for RV64 for linux targets
# WORKDIR /opt/riscv-gnu-toolchain
# RUN ./configure --prefix=/opt/riscv
# RUN make musl -j$(nproc)

# =========================== Milk-V SDK ===========================
RUN git clone https://github.com/milkv-duo/duo-sdk.git /opt/riscv/

# Add the toolchain to the PATH
ENV PATH=/opt/riscv/riscv64-linux-musl-x86_64/bin:$PATH

# =========================== RISC-V Linux Headers ===========================
RUN git clone https://github.com/torvalds/linux.git /opt/linux

WORKDIR /opt/linux

RUN make ARCH=riscv defconfig
RUN make ARCH=riscv headers_install INSTALL_HDR_PATH=/opt/riscv64-linux-headers/

# =========================== Project Sync ===========================

# Copy the project into the Docker image
COPY . /opt/miles

# Set the working directory to your project
WORKDIR /opt/miles

# Copy the build script into the Docker image
COPY build_project.sh /usr/local/bin/build_project.sh
RUN chmod +x /usr/local/bin/build_project.sh

# Set the entrypoint to a shell, allows for running commands if needed
ENTRYPOINT ["/bin/bash"]

