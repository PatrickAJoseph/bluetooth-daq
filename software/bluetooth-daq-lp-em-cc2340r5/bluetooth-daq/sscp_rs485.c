
#include "sscp_rs485.h"
#include "sscp_regs.h"
#include "sscp_app.h"

/* Control matrix definition. */
/* NOTE: Callback functions are defined in sscp_app.h */

static SSCP_REGISTER_HANDLE_LIST(sscpSerialHandleList)
{
    /* GPIO registers. */

    SSCP_REGISTER_HANDLE( 0, gpioWriteReg, gpioWriteRegCallback ),
    SSCP_REGISTER_HANDLE( 1, gpioToggleReg, gpioToggleRegCallback ),
    SSCP_REGISTER_HANDLE( 2, gpioReadReg, gpioReadRegCallback ),
    SSCP_REGISTER_HANDLE( 3, gpioPinctrlReg, gpioPinctrlRegCallback ),

    /* SPI control registers. */

    SSCP_REGISTER_HANDLE( 4, spiControlReg, spiControlRegCallback ),
    SSCP_REGISTER_HANDLE( 5, spiReadDataReg, spiReadDataRegCallback ),
    SSCP_REGISTER_HANDLE( 6, spiWriteDataReg, spiWriteDataRegCallback ),

    /* UART control registers. */

    SSCP_REGISTER_HANDLE( 7, uartPhyControlReg, uartPhyControlRegCallback ),
    SSCP_REGISTER_HANDLE( 8, uartTransferConfigReg, uartTransferConfigRegCallback ),
    SSCP_REGISTER_HANDLE( 9, uartTransferControlReg, uartTransferControlRegCallback ),
    SSCP_REGISTER_HANDLE( 10, uartReadDataReg, uartReadDataRegCallback ),
    SSCP_REGISTER_HANDLE( 11, uartWriteDataReg, uartWriteDataRegCallback ),

    /* I2C control registers. */

    SSCP_REGISTER_HANDLE( 12, i2cControlReg, i2cControlRegCallback ),
    SSCP_REGISTER_HANDLE( 13, i2cTransferConfigReg, i2cTransferConfigRegCallback ),
    SSCP_REGISTER_HANDLE( 14, i2cReadDataReg, i2cReadDataRegCallback ),
    SSCP_REGISTER_HANDLE( 15, i2cWriteDataReg, i2cWriteDataRegCallback ),
};

/* RS485 API defines this function. */

extern int RS485_write(uint8_t* byte, size_t size);

/* SSCP instance. */

SSCP_HANDLE(sscpSerialHandle, SSCP_REGISTER_HANDLE_LIST_NAME(sscpSerialHandleList), RS485_write, SSCP_DEVICE_ID);

/* Function required by RS485 layer to read a byte. */

extern int RS485_readByte();

/* RS485 callback function. */

void sscpSerialCallback(void *buf, size_t count, void *userArg, int_fast16_t status)
{
    size_t index;
    uint8_t* byte = (uint8_t*)buf;

    for( index = 0 ; index < count ; index++ )
    {
        SSCP_handleRxByte(&sscpSerialHandle, byte[index]);
    }
}

/* RS485 processing function. */

void sscpRS485Process()
{
    int ret = 0;

    do{
        ret = RS485_readByte();
    }while( ret == 0 );

    SSCP_process(&sscpSerialHandle);
}