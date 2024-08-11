#ifdef USE_SPIDEV

#include "pal/spi.h"
#include "common/logger.hpp"

#include <cstdint>
#include <cstdlib>
#include <fcntl.h>
#include <linux/spi/spi.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

SPIInterface::SPIInterface(const std::string &deviceName, uint8_t bus, uint8_t slave, uint8_t mode,
                           uint8_t bits, uint32_t speed)
{
    this->deviceName = deviceName;
    this->bus = bus;
    this->slave = slave;
    this->mode = mode;
    this->bits = bits;
    this->speed = speed;

#if defined(DEBUG_ENABLED) || defined(DEBUG_SPI)
    logger.setLogLevel(LogLevel::DEBUG);
#endif

    logger.setLogToFile("spi_spidev" + std::to_string(bus) + "." + std::to_string(slave), true);
    logger.setModuleName("SPI-" + deviceName);
}

mstatus_t SPIInterface::init()
{
    logger.info("Initializing SPI Interface");

    // Opens the device file
    std::string spi_device_path = "/dev/spidev" + std::to_string(bus) + "." + std::to_string(slave);
    logger.debug("Opening " + spi_device_path + " device file");
    fd = open(spi_device_path.c_str(), O_RDWR);
    if (fd < 0)
    {
        logger.error("Unable to open spidev device file");
        return M_ERROR;
    }

    // Configure SPI
    logger.debug("Setting SPI Mode");
    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1)
    {
        logger.error("Unable to set SPI mode");
        return M_ERROR;
    }

    logger.debug("Setting SPI bits per word");
    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1)
    {
        logger.error("Unable to set SPI bits per word");
        return M_ERROR;
    }

    logger.debug("Setting SPI speed");
    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1)
    {
        logger.error("Unable to set SPI speed");
        return M_ERROR;
    }

    return M_SUCC;
}

mstatus_t SPIInterface::spi_transfer(uint8_t *tx, uint8_t *rx, size_t len)
{
    logger.debug("Performing SPI Transfer");
    // Populates the spi_ioc_transfer struct used by spidev.
    struct spi_ioc_transfer transfer = {
        .tx_buf = (unsigned long)tx, // transmit buffer
        .rx_buf = (unsigned long)rx, // recieve buffer
        .len = (unsigned int)len,    // Length of the tx and tx buffers
        .speed_hz = this->speed,     // The clock rate
        .bits_per_word = this->bits, // Bits per frame
    };

    // If the operation failed, return an error code
    if (ioctl(fd, SPI_IOC_MESSAGE(1), &transfer) < 0)
    {
        logger.error("Transfer Error");
        return M_ERROR;
    }

    return M_SUCC;
}

SPIInterface::~SPIInterface()
{
    // If the spidev device file was opened, close it.
    if (this->fd >= 0)
    {
        close(this->fd);
    }
}

#endif // USE_SPIDEV
