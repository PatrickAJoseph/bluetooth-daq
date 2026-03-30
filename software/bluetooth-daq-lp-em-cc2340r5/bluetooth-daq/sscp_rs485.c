
#include "sscp_rs485.h"
#include "sscp_regs.h"
#include "sscp_app.h"

/* GPIO register defines. */

struct sGpioWriteReg gpioWriteReg;
struct sGpioToggleReg gpioToggleReg;
struct sGpioReadReg gpioReadReg;

/* Control matrix definition. */
/* NOTE: Callback functions are defined in sscp_app.h */

static SSCP_REGISTER_HANDLE_LIST(sscpSerialHandleList)
{
    /* GPIO registers. */

    SSCP_REGISTER_HANDLE( 0, gpioWriteReg, gpioWriteRegCallback ),
    SSCP_REGISTER_HANDLE( 1, gpioToggleReg, gpioToggleRegCallback ),
    SSCP_REGISTER_HANDLE( 2, gpioReadReg, gpioReadRegCallback ),
};

/* RS485 API defines this function. */

extern int RS485_write(uint8_t* byte, size_t size);

/* SSCP instance. */

static SSCP_HANDLE(sscpSerialHandle, SSCP_REGISTER_HANDLE_LIST_NAME(sscpSerialHandleList), RS485_write, SSCP_DEVICE_ID);

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