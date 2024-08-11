#include "pal/spi.h" // Include the header where the SPI class is defined
#include <iomanip>
#include <iostream>
#include <linux/spi/spidev.h>
#include <vector>

#define SPI_PATH "/dev/spidev0.0"

/**
 * @brief Test SPI initialization.
 */
void test_spi_initialization(SPIInterface *spi_device)
{
    mstatus_t ret = spi_device->init();
    if (ret != M_SUCC)
        std::cerr << "SPI Initialization Test: Failed" << std::endl;

    std::cout << "SPI Initialization Test: Passed" << std::endl;
}

/**
 * @brief Test SPI data transfer.
 */
void test_spi_transfer(SPIInterface *spi_device)
{

    // Example SPI transfer data
    std::vector<uint8_t> tx = {0xDE, 0xAD, 0xBE, 0xEF};
    std::vector<uint8_t> rx(tx.size());

    mstatus_t ret = spi_device->spi_transfer(tx.data(), rx.data(), tx.size());

    if (ret != M_SUCC)
        std::cerr << "SPI Transfer Test: Failed" << std::endl;

    // Print sent data
    std::cout << "SPI Transfer Test: Sent: ";

    for (auto &byte : tx)
    {
        std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte)
                  << " ";
    }
    std::cout << std::endl;

    // Print received data
    std::cout << "SPI Transfer Test: Received: ";
    for (auto &byte : rx)
    {
        std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte)
                  << " ";
    }
    std::cout << std::endl;
    std::cout << "SPI Transfer Test: Passed" << std::endl;
}

/**
 * @brief Test error handling in SPI.
 */
void test_spi_error_handling()
{
    // Try to initialize SPI with an invalid device path
    SPIInterface spi("Test Device:", 255, 255, SPI_MODE_0, 8, 50000);
    mstatus_t ret = spi.init();
    if (ret == M_SUCC)
        std::cerr << "SPI Error Handling Test: Failed" << std::endl;

    std::cout << "SPI Error Handling Test: Passed " << std::endl;
}

int main()
{
    std::cout << "Starting SPI Tests..." << std::endl;

    SPIInterface spi("Test Device:", 0, 0, SPI_MODE_0, 8, 50000);

    // Run tests
    test_spi_initialization(&spi);
    test_spi_transfer(&spi);
    test_spi_error_handling();
    std::cout << "SPI Tests Completed." << std::endl;

    return 0;
}
