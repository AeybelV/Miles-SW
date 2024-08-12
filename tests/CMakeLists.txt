cmake_minimum_required(VERSION 3.10)
project(Miles)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tests
option(TEST_SPIDEV "Test PAL SPI Interface using spidev" ON)
option(TEST_ICM20948 "Test TDK ICM-20948 IMU" ON)

# Add include directories
include_directories(../include)
include_directories(/opt/riscv64-linux-headers/include)


# ========== SPI ==========
if(TEST_SPIDEV)
  set(SPI_SOURCES ../src/pal/linux/spi.cpp spi/spi_test.cpp)
  add_executable(miles_spi_test ${SPI_SOURCES})
  target_compile_definitions(miles_spi_test PRIVATE USE_SPIDEV DEBUG_ENABLED)
endif()

# ========== ICM-20948 ==========
if(TEST_ICM20948)
  set(ICM20948_SOURCES ../src/pal/linux/spi.cpp ../src/drivers/imu/icm-20948.cpp drivers/imu/icm-20948_test.cpp)
  add_executable(miles_tdk_imu_test ${ICM20948_SOURCES})
  target_compile_definitions(miles_tdk_imu_test PRIVATE IMU_SPI_BUS=${IMU_SPI_BUS})
  target_compile_definitions(miles_tdk_imu_test PRIVATE IMU_SPI_SLAVE=${IMU_SPI_SLAVE})
  target_compile_definitions(miles_tdk_imu_test PRIVATE IMU_SPI_SPEED=${IMU_SPI_SPEED})
  target_compile_definitions(miles_tdk_imu_test PRIVATE USE_SPIDEV IMU_ICM_20948 DEBUG_ENABLED)
endif()
