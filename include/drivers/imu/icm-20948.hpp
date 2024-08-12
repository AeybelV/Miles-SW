#pragma once

// #ifdef IMU_ICM_20948

#include "common/types.h"
#include "pal/spi.h"
#include <cstdint>

// CMake will define the SPI parameters for the SPI through compile defintions.
// In the event they aren't defined, there are some default values to fallback on.
#ifndef IMU_SPI_BUS
#define IMU_SPI_BUS 1 // Fallback in case the macro is not defined
#endif
#ifndef IMU_SPI_SLAVE
#define IMU_SPI_SLAVE 1 // Fallback in case the macro is not defined
#endif
#ifndef IMU_SPI_SPEED
#define IMU_SPI_SPEED 1000 // Fallback in case the macro is not defined
#endif

// ========== IMU Registers ==========
#define ICM20948_REG_BANK_SEL 0x7F
// [User Bank 0]
#define ICM20948_UB0_WHOAMI_REG 0x00
#define ICM20948_UB0_USER_CTRL 0x03
#define ICM20948_UB0_LP_CONFIG 0x05
#define ICM20948_UB0_PWR_MGMT_1 0x06
#define ICM20948_UB0_PWR_MGMT_2 0x07
#define ICM20948_UB0_ACCEL_XOUT_H 0x2D
#define ICM20948_UB0_ACCEL_XOUT_L 0x2E
#define ICM20948_UB0_ACCEL_YOUT_H 0x2F
#define ICM20948_UB0_ACCEL_YOUT_L 0x30
#define ICM20948_UB0_ACCEL_ZOUT_H 0x31
#define ICM20948_UB0_ACCEL_ZOUT_L 0x32
// [User Bank 1]
// [User Bank 2]
#define ICM20948_UB2_GYRO_SMPLRT_DIV 0x00
#define ICM20948_UB2_GYRO_CONFIG_1 0x01
#define ICM20948_UB2_ACCEL_SMPLRT_DIV_1 0x10
#define ICM20948_UB2_ACCEL_CONFIG 0x14
// [User Bank 3]

// ========== IMU Masks and Values ==========
// Read/writes
#define ICM20948_RW_BIT 0x80
#define ICM20948_READ_ADDR(reg) ((reg) | ICM20948_RW_BIT)
#define ICM20948_WRITE_ADDR(reg) ((reg) & ~ICM20948_RW_BIT)
// Bank selection
#define ICM20948_REG_BANK_SEL_BANK_0 0x00
#define ICM20948_REG_BANK_SEL_BANK_1 0x10
#define ICM20948_REG_BANK_SEL_BANK_2 0x20
#define ICM20948_REG_BANK_SEL_BANK_3 0x30
// PWR_MGNMT_1
#define ICM20948_PWR_MGMNT_1_CLOCK_SEL_INTERNAL 0x00
#define ICM20948_PWR_MGMNT_1_CLOCK_SEL_AUTO 0x01
#define ICM20948_PWR_MGMNT_1_CLOCK_SEL_STOP 0x07
// PWR_MGNMT_2
#define ICM20948_PWR_MGMNT_2_GYRO_MASK 0x07
#define ICM20948_PWR_MGMNT_2_ACCEL_MASK 0x38
// WHO_AM_I
#define ICM20948_WHO_AM_I_VALUE 0xEA
// GYRO_CONFIG_1
#define ICM20948_GYRO_CONFIG_1_GYRO_FCHOICE 0x01
#define ICM20948_GYRO_CONFIG_1_GYRO_FS_SEL_OFFSET 0x01
#define ICM20948_GYRO_CONFIG_1_GYRO_DLPFCFG_OFFSET 0x08
#define ICM20948_GYRO_RANGE_250DPS 0x00
#define ICM20948_GYRO_RANGE_500DPS 0x01
#define ICM20948_GYRO_RANGE_1000DPS 0x10
#define ICM20948_GYRO_RANGE_2000DPS 0x11
// ACCEL_CONFIG
#define ICM20948_ACCEL_CONFIG_ACCEL_FCHOICE 0x01
#define ICM20948_ACCEL_CONFIG_ACCEL_FS_SEL_OFFSET 0x01
#define ICM20948_ACCEL_CONFIG_ACCEL_DLPFCFG_OFFSET 0x08
#define ICM20948_ACCEL_RANGE_2G 0x00
#define ICM20948_ACCEL_RANGE_4G 0x01
#define ICM20948_ACCEL_RANGE_8G 0x10
#define ICM20948_ACCEL_RANGE_16G 0x11

class ICM20948
{
  public:
    ICM20948();
    ~ICM20948();

    mstatus_t initialize();
    mstatus_t readGyro(float &gyroX, float &gyroY, float &gyroZ);
    mstatus_t readAccel(float &accelX, float &accelY, float &accelZ);
    void configure();

  private:
    SPIInterface spi;
    Logger logger;
    float gyroScaleFactor;
    float accelScaleFactor;
    mstatus_t writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
    mstatus_t changeUserBank(uint8_t bank);
    mstatus_t selectAutoClockSource();
    mstatus_t setAccelEnable(bool enable);
    mstatus_t setGyroEnable(bool enable);
    mstatus_t configureGyro(uint8_t range);
    mstatus_t configureAccel(uint8_t range);
    mstatus_t setGyroSampleRate(uint8_t rate);
    mstatus_t setAccelSampleRate(uint8_t rate);
    mstatus_t whoAmI();
};

// #endif
