#include "drivers/imu/icm-20948.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <sysexits.h>
#include <thread>

#define MEASUREMENT_CNT 150
#define MEASUREMENT_DELAY_MS 50
#define TEST_DELAY_S 5
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

    // Accelerometer X
    std::this_thread::sleep_for(std::chrono::seconds(TEST_DELAY_S)); // Delay for 3 seconds
    std::cout << "Reading Accelerometer X. Move the device on the X axis" << std::endl;
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
    std::this_thread::sleep_for(std::chrono::seconds(TEST_DELAY_S)); // Delay for 3 seconds
    std::cout << "Reading Accelerometer Y. Move the device on the Y axis" << std::endl;
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
    std::this_thread::sleep_for(std::chrono::seconds(TEST_DELAY_S)); // Delay for 3 seconds
    std::cout << "Reading Accelerometer Z. Move the device on the Z axis" << std::endl;
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
    return EX_OK;
}
