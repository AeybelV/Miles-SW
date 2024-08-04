#!/bin/bash

# This is meant to be run within the container

# Navigate to the project directory
cd /opt/miles

# Create build directory if it doesn't exist
mkdir -p build/sw
cd build/sw

# If a command-line argument is passed to the script, handle it
if [ "$1" == "configure" ]; then
  # Run cmake with the toolchain file and then ccmake for interactive configuration
  ccmake .
else
  # Run cmake with the toolchain file and then make to compile the project
  make -j$(nproc)
fi
