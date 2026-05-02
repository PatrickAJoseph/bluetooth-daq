
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

struct sUartPhyControlReg
{
    uint32_t baudRate           :   24;
    uint32_t stopBits           :   1;
    uint32_t parity             :   2;
    uint32_t reserved           :   5;
};

extern struct sUartPhyControlReg uartPhyControlReg;

struct sUartTransferConfigReg
{
    uint32_t readSize           :   8;
    uint32_t writeSize          :   8;
    uint32_t timeout            :   16;
};

extern struct sUartTransferConfigReg uartTransferConfigReg;

struct sUartTransferControlReg
{
    uint32_t mode               :   2;
    uint32_t cancel             :   1;
    uint32_t transfer           :   1;
    uint32_t readWriteInterval  :   16;
    uint32_t reserved           :   12;
};

extern struct sUartTransferControlReg uartTransferControlReg;

struct sUartReadDataReg
{
    uint32_t index              :   8;
    uint32_t byte               :   8;
    uint32_t readCount          :   8;
    uint32_t reserved           :   8;
};

extern struct sUartReadDataReg uartReadDataReg;

struct sUartWriteDataReg
{
    uint32_t index              :   8;
    uint32_t byte               :   8;
    uint32_t reserved           :   16;
};

extern struct sUartWriteDataReg uartWriteDataReg;

struct sI2CControlReg
{
    uint32_t fastModeEnable   :     1;
    uint32_t targetAddress    :     8;
    uint32_t timeout          :     23;
};

extern struct sI2CControlReg i2cControlReg;

struct sI2CTransferConfigReg
{
    uint32_t readSize          :    8;
    uint32_t writeSize         :    8;
    uint32_t status            :    3;
    uint32_t transfer          :    1;
    uint32_t reserved          :    12;
};

extern struct sI2CTransferConfigReg i2cTransferConfigReg;

struct sI2CReadDataReg
{
    uint32_t index              :   8;
    uint32_t byte               :   8;
    uint32_t reserved           :   16;
};

extern struct sI2CReadDataReg i2cReadDataReg;

struct sI2CWriteDataReg
{
    uint32_t index              :   8;
    uint32_t byte               :   8;
    uint32_t reserved           :   16;
};

extern struct sI2CWriteDataReg i2cWriteDataReg;

struct sDacControlReg
{
    uint32_t index              :   16;
    uint32_t voltage            :   16;
};

extern struct sDacControlReg dacControlReg;

struct sHsAdcControlReg
{
    uint32_t numberOfSamples    :   10;
    uint32_t dualMode           :   1;
    uint32_t start              :   1;
    uint32_t reserved           :   20;
};

extern struct sHsAdcControlReg hsAdcControlReg;

struct sHsAdcSamplesReg
{
    uint32_t channel            :   1;
    uint32_t index              :   10;
    uint32_t sample             :   17;
    uint32_t reserved           :   4;
};

extern struct sHsAdcSamplesReg hsAdcSamplesReg;

#endif /* SSCP_REGS_H */