#!/bin/bash

ARCH=$1
CMAKE_TOOLCHAIN=$2
# Navigate to the project directory
cd /opt/miles

# Create build directory if it doesn't exist
mkdir -p build/sw

# Setups CMake
# This is where toolchains are passed in
cmake -DCMAKE_TOOLCHAIN_FILE=$(pwd)/toolchain/$ARCH/$CMAKE_TOOLCHAIN.toolchain.cmake -S . -B build/sw
# If a command-line argument is passed to the script, handle it
if [ "$3" == "build" ]; then
  cd build/sw
  echo "Starting build of robot software"
  # Run cmake with the toolchain file and then ccmake for interactive configuration
  make -j$(nproc)
fi
