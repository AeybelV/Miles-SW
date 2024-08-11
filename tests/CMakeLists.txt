cmake_minimum_required(VERSION 3.10)
project(Miles)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tests
option(TEST_SPIDEV "Test PAL SPI Interface using spidev" ON)

# Add include directories
include_directories(../include)
include_directories(/opt/riscv64-linux-headers/include)


# ========== SPI ==========
if(TEST_SPIDEV)
  set(SPI_SOURCES ../src/pal/linux/spi.cpp spi/spi_test.cpp)
  add_executable(miles_spi_test ${SPI_SOURCES})
  target_compile_definitions(miles_spi_test PRIVATE USE_SPIDEV)
endif()
