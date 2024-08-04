cmake_minimum_required(VERSION 3.10)
project(Miles)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# riscv.toolchain.cmake
# Define the C compiler and C++ compiler for RISC-V
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR riscv64)

# Specify the cross compiler
SET(CMAKE_C_COMPILER /opt/riscv/bin/riscv64-unknown-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER /opt/riscv/bin/riscv64-unknown-linux-gnu-g++)

# Specify the target environment
SET(CMAKE_FIND_ROOT_PATH /opt/riscv/riscv64-linux-gnu)

# Add compile-time options
option(USE_WIRINGX "Use wiringX library for hardware communication" ON)

# Define sources and headers
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Add include directories
include_directories(include)

# Add executable
add_executable(Miles ${SOURCES})

# Link libraries based on options
if(USE_WIRINGX)
  target_compile_definitions(Miles PRIVATE USE_WIRINGX)
  target_link_libraries(Miles wiringX)
endif()

# Enable testing
enable_testing()
add_subdirectory(tests)

