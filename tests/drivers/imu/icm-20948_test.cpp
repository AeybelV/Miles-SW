#include "drivers/imu/icm-20948.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <sysexits.h>
#include <thread>

#define MEASUREMENT_CNT 500
#define MEASUREMENT_DELAY_MS 25
#define TEST_DELAY_S 3

struct IMU_AXES
{
    float x, y, z;
};

void writeAxisToFile(std::string filename, IMU_AXES *data, size_t length)
{
    std::ofstream file(filename);

    if (file.is_open())
    {
        // Step 3: Write the header
        file << "x,y,z\n";

        // Write the array data to the file
        for (int i = 0; i < length; ++i)
        {
            file << data[i].x << ',' << data[i].y << ',' << data[i].z << '\n';
        }

        // Close the file
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing\n";
    }
}

void testAccelerometer(ICM20948 &imu)
{
    // ==================== Accelerometer ====================

    std::cout << "[Accelerometer test]" << std::endl;
    // Accelerometer X
    std::this_thread::sleep_for(std::chrono::seconds(TEST_DELAY_S));
    std::cout << "Reading Accelerometer X. Move the device on the X axis" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    IMU_AXES movement_accel_x[MEASUREMENT_CNT];
    for (size_t i = 0; i < MEASUREMENT_CNT; i++)
    {
        IMU_AXES accel_data;
        imu.readAccel(accel_data.x, accel_data.y, accel_data.z);
        movement_accel_x[i] = accel_data;
        std::this_thread::sleep_for(std::chrono::milliseconds(MEASUREMENT_DELAY_MS));
    }
    writeAxisToFile("X_ACCEL.csv", movement_accel_x, MEASUREMENT_CNT);
    std::cout << "Recorded data can be found in X_ACCEL.csv" << std::endl;

    // Accelerometer Y
    std::this_thread::sleep_for(std::chrono::seconds(TEST_DELAY_S));
    std::cout << "Reading Accelerometer Y. Move the device on the Y axis" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    IMU_AXES movement_accel_y[MEASUREMENT_CNT];
    for (size_t i = 0; i < MEASUREMENT_CNT; i++)
    {
        IMU_AXES accel_data;
        imu.readAccel(accel_data.x, accel_data.y, accel_data.z);
        movement_accel_y[i] = accel_data;
        std::this_thread::sleep_for(std::chrono::milliseconds(MEASUREMENT_DELAY_MS));
    }
    writeAxisToFile("Y_ACCEL.csv", movement_accel_y, MEASUREMENT_CNT);
    std::cout << "Recorded data can be found in Y_ACCEL.csv" << std::endl;

    // Accelerometer Z
    std::this_thread::sleep_for(std::chrono::seconds(TEST_DELAY_S));
    std::cout << "Reading Accelerometer Z. Move the device on the Z axis" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    IMU_AXES movement_accel_z[MEASUREMENT_CNT];
    for (size_t i = 0; i < MEASUREMENT_CNT; i++)
    {
        IMU_AXES accel_data;
        imu.readAccel(accel_data.x, accel_data.y, accel_data.z);
        movement_accel_z[i] = accel_data;
        std::this_thread::sleep_for(std::chrono::milliseconds(MEASUREMENT_DELAY_MS));
    }
    writeAxisToFile("Z_ACCEL.csv", movement_accel_z, MEASUREMENT_CNT);
    std::cout << "Recorded data can be found in Z_ACCEL.csv" << std::endl;
    std::cout << "Accelerometer test complete" << std::endl;
}

void testGyroscope(ICM20948 &imu)
{
    // ==================== Gyroscope ====================

    std::cout << "[Gyroscope test]" << std::endl;
    // Gyroscope X
    std::this_thread::sleep_for(std::chrono::seconds(TEST_DELAY_S));
    std::cout << "Reading Gyroscope X. Move the device on the X axis" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    IMU_AXES movement_gyro_x[MEASUREMENT_CNT];
    for (size_t i = 0; i < MEASUREMENT_CNT; i++)
    {
        IMU_AXES gyro_data;
        imu.readGyro(gyro_data.x, gyro_data.y, gyro_data.z);
        movement_gyro_x[i] = gyro_data;
        std::this_thread::sleep_for(std::chrono::milliseconds(MEASUREMENT_DELAY_MS));
    }
    writeAxisToFile("X_GYRO.csv", movement_gyro_x, MEASUREMENT_CNT);
    std::cout << "Recorded data can be found in X_GYRO.csv" << std::endl;

    // Gyroscope Y
    std::this_thread::sleep_for(std::chrono::seconds(TEST_DELAY_S));
    std::cout << "Reading Gyroscope Y. Move the device on the Y axis" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    IMU_AXES movement_gyro_y[MEASUREMENT_CNT];
    for (size_t i = 0; i < MEASUREMENT_CNT; i++)
    {
        IMU_AXES gyro_data;
        imu.readGyro(gyro_data.x, gyro_data.y, gyro_data.z);
        movement_gyro_y[i] = gyro_data;
        std::this_thread::sleep_for(std::chrono::milliseconds(MEASUREMENT_DELAY_MS));
    }
    writeAxisToFile("Y_GYRO.csv", movement_gyro_y, MEASUREMENT_CNT);
    std::cout << "Recorded data can be found in Y_GYRO.csv" << std::endl;

    // Gyroscope Z
    std::this_thread::sleep_for(std::chrono::seconds(TEST_DELAY_S));
    std::cout << "Reading Gyroscope Z. Move the device on the Z axis" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    IMU_AXES movement_gyro_z[MEASUREMENT_CNT];
    for (size_t i = 0; i < MEASUREMENT_CNT; i++)
    {
        IMU_AXES gyro_data;
        imu.readGyro(gyro_data.x, gyro_data.y, gyro_data.z);
        movement_gyro_z[i] = gyro_data;
        std::this_thread::sleep_for(std::chrono::milliseconds(MEASUREMENT_DELAY_MS));
    }
    writeAxisToFile("Z_GYRO.csv", movement_gyro_z, MEASUREMENT_CNT);
    std::cout << "Recorded data can be found in Z_GYRO.csv" << std::endl;
    std::cout << "Gyroscope test complete" << std::endl;
}

int main(int argc, char *argv[])
{
    ICM20948 imu;

    mstatus_t init_ret = imu.initialize();
    if (init_ret != M_SUCC)
    {
        std::cerr << "IMU Initialization Test: Failed" << std::endl;
        return EX_IOERR;
    }
    std::cout << "IMU Initialization Passed" << std::endl;

    testAccelerometer(imu);
    testGyroscope(imu);

    return EX_OK;
}
