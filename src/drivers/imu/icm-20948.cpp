#include "drivers/imu/icm-20948.hpp"
#include "common/types.h"
#include <cstdint>
#include <linux/spi/spi.h>
// #ifdef IMU_ICM_20948

ICM20948::ICM20948()
    : spi("TDK ICM-2048", IMU_SPI_BUS, IMU_SPI_SLAVE, SPI_MODE_3, 16, IMU_SPI_SPEED)
{
    logger.setLogToFile("ICM-20948.log", true);
    logger.setModuleName("ICM-2048");
}

ICM20948::~ICM20948()
{
}

uint8_t ICM20948::readRegister(uint8_t reg)
{
    uint8_t spi_data[2] = {0, (uint8_t)ICM20948_READ_ADDR(reg)};
    uint8_t rx[2];
    spi.spi_transfer(spi_data, rx, sizeof(spi_data));
    return rx[0];
}

mstatus_t ICM20948::writeRegister(uint8_t reg, uint8_t value)
{
    uint8_t spi_data[2] = {value, (uint8_t)ICM20948_WRITE_ADDR(reg)};
    uint8_t rx[2];
    return spi.spi_transfer(spi_data, rx, sizeof(spi_data));
}

mstatus_t ICM20948::changeUserBank(uint8_t bank)
{
    // Make sure the bank passed in is a valid value
    if (bank != ICM20948_REG_BANK_SEL_BANK_0 && bank != ICM20948_REG_BANK_SEL_BANK_1 &&
        bank != ICM20948_REG_BANK_SEL_BANK_2 && bank != ICM20948_REG_BANK_SEL_BANK_3)
        return M_ERROR;
    return writeRegister(ICM20948_REG_BANK_SEL, bank);
}

mstatus_t ICM20948::selectAutoClockSource()
{
    changeUserBank(ICM20948_REG_BANK_SEL_BANK_0);
    return writeRegister(ICM20948_UB0_PWR_MGMT_1, ICM20948_PWR_MGMNT_1_CLOCK_SEL_AUTO);
}

mstatus_t ICM20948::whoAmI()
{
    changeUserBank(ICM20948_REG_BANK_SEL_BANK_0);
    uint8_t who_id = readRegister(ICM20948_UB0_WHOAMI_REG);
    // If the value read doesn't match the expected value, return an error
    if (who_id != ICM20948_WHO_AM_I_VALUE)
        return M_ERROR;

    return M_SUCC;
}

mstatus_t ICM20948::setAccelEnable(bool enable)
{
    // Reads currently enabled devices
    changeUserBank(ICM20948_REG_BANK_SEL_BANK_0);
    uint8_t pwr_mgmnt_curr = readRegister(ICM20948_UB0_PWR_MGMT_2);
    // Sets the power state for accelerometer
    if (enable)
    {
        // Clears the bit field to enable all axes
        pwr_mgmnt_curr = pwr_mgmnt_curr & ~ICM20948_PWR_MGMNT_2_ACCEL_MASK;
    }
    else
    {
        // Sets the bit field to disnable all axes
        pwr_mgmnt_curr = pwr_mgmnt_curr | ICM20948_PWR_MGMNT_2_ACCEL_MASK;
    }
    // Writes it back
    writeRegister(ICM20948_UB0_PWR_MGMT_2, pwr_mgmnt_curr);
    return M_SUCC;
}

mstatus_t ICM20948::setGyroEnable(bool enable)
{
    // Reads currently enabled devices
    changeUserBank(ICM20948_REG_BANK_SEL_BANK_0);
    uint8_t pwr_mgmnt_curr = readRegister(ICM20948_UB0_PWR_MGMT_2);
    // Sets the power state for gyroscope
    if (enable)
    {
        // Clears the bit field to enable all axes
        pwr_mgmnt_curr = pwr_mgmnt_curr & ~ICM20948_PWR_MGMNT_2_GYRO_MASK;
    }
    else
    {
        // Sets the bit field to disnable all axes
        pwr_mgmnt_curr = pwr_mgmnt_curr | ICM20948_PWR_MGMNT_2_GYRO_MASK;
    }
    // Writes it back
    writeRegister(ICM20948_UB0_PWR_MGMT_2, pwr_mgmnt_curr);
    return M_SUCC;
}

mstatus_t ICM20948::configureGyro(uint8_t range)
{
    changeUserBank(ICM20948_REG_BANK_SEL_BANK_2);
    // TODO: Have gyroscope filter options configurable maybe?
    uint8_t gyro_config = 0;
    // Enable Gyro DLPF
    gyro_config |= ICM20948_GYRO_CONFIG_1_GYRO_FCHOICE;
    // Gyro full scale select
    gyro_config |= (((range) & 0b11) << ICM20948_GYRO_CONFIG_1_GYRO_FS_SEL_OFFSET);
    // Gyro low pass filter config.
    // Hardcoded to use 5
    gyro_config |= ((5 & 0b111) << ICM20948_GYRO_CONFIG_1_GYRO_DLPFCFG_OFFSET);
    writeRegister(ICM20948_UB2_ACCEL_CONFIG, gyro_config);

    // Sets scale factor
    switch (range)
    {
    case ICM20948_GYRO_RANGE_250DPS:
    {
        gyroScaleFactor = 131.0f;
        break;
    }
    case ICM20948_GYRO_RANGE_500DPS:
    {
        gyroScaleFactor = 65.5f;
        break;
    }
    case ICM20948_GYRO_RANGE_1000DPS:
    {
        gyroScaleFactor = 32.8f;
        break;
    }
    case ICM20948_GYRO_RANGE_2000DPS:
    {
        gyroScaleFactor = 16.4f;
        break;
    }
    default:
        gyroScaleFactor = 131;
    }
    return M_SUCC;
}

mstatus_t ICM20948::configureAccel(uint8_t range)
{
    changeUserBank(ICM20948_REG_BANK_SEL_BANK_2);
    // TODO: Have accelerometer filter options configurable maybe?
    uint8_t accel_config = 0;
    // Enable Accel DLPF
    accel_config |= ICM20948_ACCEL_CONFIG_ACCEL_FCHOICE;
    // Accel full scale select
    accel_config |= (((range) & 0b11) << ICM20948_ACCEL_CONFIG_ACCEL_FS_SEL_OFFSET);
    // Accel low pass filter config.
    // Hardcoded to use 5
    accel_config |= ((5 & 0b111) << ICM20948_ACCEL_CONFIG_ACCEL_DLPFCFG_OFFSET);
    writeRegister(ICM20948_UB2_ACCEL_CONFIG, accel_config);

    switch (range)
    {
    case ICM20948_ACCEL_RANGE_2G:
    {
        accelScaleFactor = 16384.0f;
        break;
    }
    case ICM20948_ACCEL_RANGE_4G:
    {
        accelScaleFactor = 8192.0f;
        break;
    }
    case ICM20948_ACCEL_RANGE_8G:
    {
        accelScaleFactor = 4096.0f;
        break;
    }
    case ICM20948_ACCEL_RANGE_16G:
    {
        accelScaleFactor = 2048.0f;
        break;
    }
    default:
        accelScaleFactor = 16384.0f;
    }
    return M_SUCC;
}

mstatus_t ICM20948::setGyroSampleRate(uint8_t rate)
{
    changeUserBank(ICM20948_REG_BANK_SEL_BANK_2);
    writeRegister(ICM20948_UB2_GYRO_SMPLRT_DIV, rate & 0xFF);
    return M_SUCC;
}

mstatus_t ICM20948::setAccelSampleRate(uint8_t rate)
{
    changeUserBank(ICM20948_REG_BANK_SEL_BANK_2);
    writeRegister(ICM20948_UB2_ACCEL_SMPLRT_DIV_1, rate & 0xFF);
    return M_SUCC;
}

mstatus_t ICM20948::readAccel(float &accelX, float &accelY, float &accelZ)
{
    changeUserBank(ICM20948_REG_BANK_SEL_BANK_0);
    // TODO: Might be more performant to have a multiple register read
    uint8_t accel_xout_h = readRegister(ICM20948_UB0_ACCEL_XOUT_H);
    uint8_t accel_xout_l = readRegister(ICM20948_UB0_ACCEL_XOUT_L);
    uint8_t accel_yout_h = readRegister(ICM20948_UB0_ACCEL_YOUT_H);
    uint8_t accel_yout_l = readRegister(ICM20948_UB0_ACCEL_YOUT_L);
    uint8_t accel_zout_h = readRegister(ICM20948_UB0_ACCEL_ZOUT_H);
    uint8_t accel_zout_l = readRegister(ICM20948_UB0_ACCEL_ZOUT_L);

    // Packs upper and lower byte
    int16_t x = ((int16_t)accel_xout_h << 8) | accel_xout_l;
    int16_t y = ((int16_t)accel_yout_h << 8) | accel_yout_l;
    int16_t z = ((int16_t)accel_zout_h << 8) | accel_zout_l;

    // Yields acceleration in m/s^2
    accelX = (x / accelScaleFactor) * 9.8f;
    accelY = (y / accelScaleFactor) * 9.8f;
    accelZ = (z / accelScaleFactor) * 9.8f;

    return M_SUCC;
}

mstatus_t ICM20948::readGyro(float &gyroX, float &gyroY, float &gyroZ)
{
    changeUserBank(ICM20948_REG_BANK_SEL_BANK_0);
    // TODO: Might be more performant to have a multiple register read
    uint8_t gyro_xout_h = readRegister(ICM20948_UB0_ACCEL_XOUT_H);
    uint8_t gyro_xout_l = readRegister(ICM20948_UB0_ACCEL_XOUT_L);
    uint8_t gyro_yout_h = readRegister(ICM20948_UB0_ACCEL_YOUT_H);
    uint8_t gyro_yout_l = readRegister(ICM20948_UB0_ACCEL_YOUT_L);
    uint8_t gyro_zout_h = readRegister(ICM20948_UB0_ACCEL_ZOUT_H);
    uint8_t gyro_zout_l = readRegister(ICM20948_UB0_ACCEL_ZOUT_L);

    // Packs upper and lower byte
    int16_t x = ((int16_t)gyro_xout_h << 8) | gyro_xout_l;
    int16_t y = ((int16_t)gyro_yout_h << 8) | gyro_yout_l;
    int16_t z = ((int16_t)gyro_zout_h << 8) | gyro_zout_l;

    // Yields angular acceleration in rad/s^2
    gyroX = (x / gyroScaleFactor) * (3.14159265359f / 180.0f);
    gyroY = (y / gyroScaleFactor) * (3.14159265359f / 180.0f);
    gyroZ = (z / gyroScaleFactor) * (3.14159265359f / 180.0f);

    return M_SUCC;
}
mstatus_t ICM20948::initialize()
{
    logger.info("Initializing TDK ICM-20948 IMU");
    mstatus_t spiInitRet = spi.init();

    if (spiInitRet != M_SUCC)
    {
        logger.error("Error initializing SPI for ICM-2048");
        return M_ERROR;
    }

    // Sends first command to see if it suceeds. Sets the user bank register to bank 0
    mstatus_t first_command = changeUserBank(ICM20948_REG_BANK_SEL_BANK_0);
    if (first_command != M_SUCC)
    {
        logger.error("Error sending commands");
        return M_ERROR;
    }

    // Initializing the ICM

    // 1. Configure clock source
    selectAutoClockSource();
    // Check if device is up by checking WHO_AM_I
    mstatus_t who_id_valid = whoAmI();
    if (who_id_valid != M_SUCC)
    {
        logger.error("IMU WHO_AM_I returned a invalid value");
        return M_ERROR;
    }
    // 2. Enable Accelerometer and Gyro
    setAccelEnable(true);
    setGyroEnable(true);
    // 3. TODO: Configure Accel/Gyro in Low Power Mode

    // 4. Set Gyro FSR to 2000dps
    configureGyro(ICM20948_GYRO_RANGE_2000DPS);
    // 5. Set Accel FSR to 4g
    configureAccel(ICM20948_ACCEL_RANGE_4G);

    // Sets a sample rate for the accelerometer and gyroscope
    setGyroSampleRate(0);
    setAccelSampleRate(0);
    return M_SUCC;
}

// #endif
