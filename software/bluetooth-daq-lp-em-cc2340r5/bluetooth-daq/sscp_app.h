#ifndef SSCP_APP_H
#define SSCP_APP_H

/* Application function definitions. */

extern void gpioWriteRegCallback(void* reg, int operation);
extern void gpioToggleRegCallback(void* reg, int operation);
extern void gpioReadRegCallback(void* reg, int operation);
extern void gpioPinctrlRegCallback(void* reg, int operation);
extern void spiControlRegCallback(void* reg, int operation);
extern void spiReadDataRegCallback(void* reg, int operation);
extern void spiWriteDataRegCallback(void* reg, int operation);
extern void uartPhyControlRegCallback(void* reg, int operation);
extern void uartTransferConfigRegCallback(void* reg, int operation);
extern void uartTransferControlRegCallback(void* reg, int operation);
extern void uartReadDataRegCallback(void* reg, int operation);
extern void uartWriteDataRegCallback(void* reg, int operation);
extern void i2cControlRegCallback(void* reg, int operation);
extern void i2cTransferConfigRegCallback(void* reg, int operation);
extern void i2cReadDataRegCallback(void* reg, int operation);
extern void i2cWriteDataRegCallback(void* reg, int operation);

#endif /* SSCP_APP */