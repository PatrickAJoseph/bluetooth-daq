
#include "sscp.h"
#include "sscp_app.h"
#include "sscp_regs.h"
#include "types.h"

/* ========== GPIO control ========== */

struct sGpioWriteReg gpioWriteReg;
struct sGpioToggleReg gpioToggleReg;
struct sGpioReadReg gpioReadReg;
struct sGpioPinctrlReg gpioPinctrlReg;

extern struct dioHandle dioHandle;

extern int DIO_writeOutput(uint16_t value);
extern int DIO_readInput();

void gpioWriteRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sGpioWriteReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {
        regs->value = dioHandle.output; 
    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        dioHandle.output = regs->value;
        DIO_writeOutput(dioHandle.output);
    }
}

void gpioToggleRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sGpioToggleReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {

    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        dioHandle.output ^= regs->value;
        DIO_writeOutput(dioHandle.output);        
    }
}

void gpioReadRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sGpioReadReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {
        DIO_readInput();
        regs->value = dioHandle.input;        
    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {

    }
}

void gpioPinctrlRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sGpioPinctrlReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {
        if( regs->read && regs->selectDigitalInput )
        {
            DIO_readInput();
            regs->value = ( ( dioHandle.input & ( 1U << regs->pinIndex ) ) ? 1 : 0 );
        }
    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        if( regs->write )
        {
            if( regs->selectDigitalInput == 0 )
            {
                dioHandle.output &= ~( 1U << regs->pinIndex );
                dioHandle.output |= ( regs->value << regs->pinIndex );
            
                DIO_writeOutput(dioHandle.output);
            }
        }
        else if( regs->toggle )
        {
            if( regs->selectDigitalInput == 0 )
            {
                dioHandle.output ^= ( 1U << regs->pinIndex );

                DIO_writeOutput(dioHandle.output);
            }
        }
    }
}

/* ========== SPI control ========== */

struct sSpiControlReg spiControlReg;
struct sSpiReadDataReg spiReadDataReg;
struct sSpiWriteDataReg spiWriteDataReg;

extern int XSPI_setBitRate(int bitRate);
extern int XSPI_setFrameFormat(unsigned int frameFormat);
extern int XSPI_setTransferSize(size_t size);
extern int XSPI_txBufferWriteByte(int index, uint8_t byte);
extern int XSPI_rxBufferReadByte(int index);
extern void XSPI_setChipSelectPolarity(unsigned int polarity);
extern int XSPI_transfer();

uint32_t xspiStatus = 0;

void spiControlRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    uint32_t temp; 
    struct sSpiControlReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {
        regs->status = xspiStatus;
    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        temp = (regs->bitRate * 10000U);

        xspiStatus = XSPI_setBitRate((int)temp);
        xspiStatus = XSPI_setFrameFormat(regs->frameFormat);
        XSPI_setChipSelectPolarity(regs->chipSelectPolarity);
        xspiStatus = XSPI_setTransferSize(regs->transferSize);

        if( regs->transfer )
        {
            xspiStatus = XSPI_transfer();
        }
    }
}

void spiWriteDataRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sSpiWriteDataReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {
        
    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        xspiStatus = XSPI_txBufferWriteByte(regs->index, regs->byte);
    }
}

void spiReadDataRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    int ret;

    struct sSpiWriteDataReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {
        ret = XSPI_rxBufferReadByte(regs->index);

        if( ret < 0 )
        {
            xspiStatus = ret;
        }
        else
        {
            xspiStatus = 0;
        }

        regs->byte = (uint8_t)ret;
    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {

    }
}