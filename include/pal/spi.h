#pragma once

#include "common/logger.hpp"
#include "common/types.h"
#include <cstddef>
#include <cstdint>
#include <string>

class SPIInterface
{
  private:
    int fd;
    uint8_t mode;
    uint8_t bits;
    uint32_t speed;
    std::string deviceName;
    Logger logger;

  public:
    /**
     * @brief Construct a new SPI object
     *
     * @param deviceName Name of the SPI Device
     * @param mode SPI mode (e.g., SPI_MODE_0), uses spidev spi modes.
     * @param bits Number of bits per word.
     * @param speed Maximum SPI speed in Hz.
     */
    SPIInterface(const std::string &deviceName, uint8_t mode, uint8_t bits, uint32_t speed);

    /**
     * @brief Cleans up SPI resources
     */
    ~SPIInterface();

    /**
     * @brief Initialize the SPI interface
     * @return mstatus_t status code
     */
    mstatus_t init();

    /**
     * @brief Perform an SPI data transfer.
     *
     * @param tx Pointer to the data to be transmitted.
     * @param rx Pointer to the buffer to store received data.
     * @param len Length of the data to be transferred. Reflects the size of both tx and rx buffer.
     * @return mstatus_t status code
     */
    mstatus_t spi_transfer(uint8_t *tx, uint8_t *rx, size_t len);
};
