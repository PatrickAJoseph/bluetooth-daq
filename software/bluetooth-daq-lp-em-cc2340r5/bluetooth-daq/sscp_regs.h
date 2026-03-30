
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

#endif /* SSCP_REGS_H */