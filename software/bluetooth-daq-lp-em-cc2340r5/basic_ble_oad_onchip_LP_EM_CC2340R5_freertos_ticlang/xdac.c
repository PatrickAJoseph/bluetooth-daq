#include <ti/drivers/I2C.h>

#define XDAC_I2C_ADDRESS        (0x60)

I2C_Transaction xdacI2cTransaction;
extern I2C_Handle i2cHandle;

static uint8_t xdacTxBuffer[3];
int xdacRet = 1000;

void xdac_writeOutput(uint16_t value)
{
    xdacI2cTransaction.targetAddress = XDAC_I2C_ADDRESS;
    xdacI2cTransaction.readBuf = NULL;
    xdacI2cTransaction.readCount = 0;
    xdacI2cTransaction.writeBuf = xdacTxBuffer;
    xdacI2cTransaction.writeCount = 3;

    xdacTxBuffer[0] = 0x40;
    xdacTxBuffer[1] = ( (value >> 4) & 0xFF );
    xdacTxBuffer[2] = ( ( value << 4 ) & 0xF0);

    int ret;

    xdacRet = I2C_transferTimeout(i2cHandle, &xdacI2cTransaction, 10000000);

    if( xdacRet < 0 )
    {
        __asm volatile("bkpt 0");
    }
}

void xdac_init()
{ 
    xdac_writeOutput(0);
}