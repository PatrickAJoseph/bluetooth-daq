
#ifndef SSCP_REGS_H
#define SSCP_REGS_H

#include <stdint.h>

#define SSCP_DEVICE_ID          0

struct sGpioWriteReg
{
    uint32_t value      : 16;
    uint32_t reserved   : 16;
};

extern struct sGpioWriteReg gpioWriteReg;

struct sGpioToggleReg
{
    uint32_t value      : 16;
    uint32_t reserved   : 16;
};

extern struct sGpioToggleReg gpioToggleReg;

struct sGpioReadReg
{
    uint32_t value      : 16;
    uint32_t reserved   : 16;
};

extern struct sGpioReadReg gpioReadReg;

struct sGpioPinctrlReg
{
    uint32_t selectDigitalInput :   1;
    uint32_t pinIndex           :   4;
    uint32_t read               :   1;
    uint32_t write              :   1;
    uint32_t toggle             :   1;
    uint32_t value              :   1;
    uint32_t reserved           :   23;
};

extern struct sGpioPinctrlReg gpioPinctrlReg;

struct sSpiControlReg
{
    /* Actual bit rate = bit rate * 10000. */
    uint32_t bitRate            :   11;
    uint32_t frameFormat        :   2;
    uint32_t transferSize       :   8;
    uint32_t chipSelectPolarity :   1;
    uint32_t transfer           :   1;
    uint32_t status             :   3;
    uint32_t reserved           :   6;
};

extern struct sSpiControlReg spiControlReg;

struct sSpiReadDataReg
{
    uint32_t index              :   8;
    uint32_t byte               :   8;
    uint32_t reserved           :   16;
};

extern struct sSpiReadDataReg spiReadDataReg;

struct sSpiWriteDataReg
{
    uint32_t index              :   8;
    uint32_t byte               :   8;
    uint32_t reserved           :   16;
};

extern struct sSpiWriteDataReg spiWriteDataReg;

#endif /* SSCP_REGS_H */