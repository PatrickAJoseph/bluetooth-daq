
#include "sscp_ble.h"
#include "sscp_regs.h"
#include "sscp_app.h"

/* Control matrix definition. */
/* NOTE: Callback functions are defined in sscp_app.h */

static SSCP_REGISTER_HANDLE_LIST(sscpBleHandleList)
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

    /* DAC control registers. */

    SSCP_REGISTER_HANDLE( 16, dacControlReg, dacControlRegCallback ),

    /* High speed ADC registers. */

    SSCP_REGISTER_HANDLE( 17, hsAdcControlReg, hsadcControlRegCallback ),
    SSCP_REGISTER_HANDLE( 18, hsAdcSamplesReg, hsadcSamplesRegCallback ),
};


extern uint8_t SSCP_bleResponsePacket[16];

int ble_write(uint8_t* byte, size_t size)
{
    int index;

    for( index = 0 ; index < ((int)size) ; index++ )
    {
        SSCP_bleResponsePacket[index] = byte[index];
    }    
}

/* SSCP instance. */

SSCP_HANDLE(sscpBleHandle, SSCP_REGISTER_HANDLE_LIST_NAME(sscpBleHandleList), ble_write, SSCP_DEVICE_ID);

/* RS485 processing function. */

void sscpBleProcess()
{
    SSCP_process(&sscpBleHandle);
}