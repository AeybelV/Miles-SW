cmake_minimum_required(VERSION 3.10)
project(Miles)

# ========== SPI ==========
option(USE_SPIDEV "Use spidev for spi communication" ON)

# ========== IMU ==========
set(IMU_SPI_BUS 0)
set(IMU_SPI_SLAVE 0)
set(IMU_SPI_SPEED 1000000)

option(IMU_ICM_20948 "Use the TDK ICM-20948 IMU" ON)

# ========== TESTS ==========
option(ENABLE_TESTING "Enable compilation of tests" ON)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ========== CMake ==========

MESSAGE(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
MESSAGE(STATUS "Using compiler: ${CMAKE_C_COMPILER}")

# Define sources and headers
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Add include directories
include_directories(include)
include_directories(/opt/riscv64-linux-headers/include)

# Add executable
add_executable(Miles ${SOURCES})

if(USE_SPIDEV)
  target_compile_definitions(Miles PUBLIC USE_SPIDEV)
endif()

target_compile_definitions(Miles PUBLIC IMU_SPI_BUS=${IMU_SPI_BUS})
target_compile_definitions(Miles PUBLIC IMU_SPI_SLAVE=${IMU_SPI_SLAVE})
target_compile_definitions(Miles PUBLIC IMU_SPI_SPEED=${IMU_SPI_SPEED})

# Debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(Miles PUBLIC DEBUG_ENABLED)
endif()

# Enable testing
if(ENABLE_TESTING)
  MESSAGE(STATUS "Tests are enabled")
  # enable_testing() # Adds tests to run on host after the build here
  add_subdirectory(tests)
endif()

