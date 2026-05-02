
#include <stdbool.h>

#include "sscp.h"
#include "sscp_app.h"
#include "sscp_regs.h"
#include "types.h"

#include <ti/posix/ticlang/sys/types.h>

extern int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
extern int pthread_mutex_lock(pthread_mutex_t *mutex);
extern int pthread_mutex_unlock(pthread_mutex_t *mutex);

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

/* ========== UART control ========== */

struct sUartPhyControlReg uartPhyControlReg;
struct sUartTransferConfigReg uartTransferConfigReg;
struct sUartTransferControlReg uartTransferControlReg;
struct sUartReadDataReg uartReadDataReg;
struct sUartWriteDataReg uartWriteDataReg;

extern int XUART_setBaudRate(int baudRate);
extern int XUART_setParity(int parity);
extern int XUART_setStopBits(int stopBits);
extern int XUART_setWriteSize(int size);
extern int XUART_setReadSize(int size);
extern int XUART_setReceiveTimeout(int timeout);
extern int XUART_receiveByteCount();
extern int XUART_transmit();
extern int XUART_receive();
extern int XUART_rxBufferReadByte(int index);
extern int XUART_txBufferWriteByte(int index, uint8_t byte);
extern int XUART_readThenWrite();
extern int XUART_writeThenRead();
extern int XUART_setReadWriteInterval(int interval);

void uartPhyControlRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sUartPhyControlReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {

    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        XUART_setBaudRate((int)regs->baudRate);
        XUART_setParity((int)regs->parity);
        XUART_setStopBits((int)regs->stopBits);
    }
}

void uartTransferConfigRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sUartTransferConfigReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {

    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        XUART_setWriteSize(regs->writeSize);
        XUART_setReadSize(regs->readSize);
        XUART_setReceiveTimeout(regs->timeout);
    }
}

void uartTransferControlRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sUartTransferControlReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {

    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        XUART_setReadWriteInterval(regs->readWriteInterval);

        if( regs->transfer )
        {
            /* Transmit. */

            if( regs->mode == 0 )
            {
                XUART_transmit();
            }
            else if( regs->mode == 1 )  /* Receive */
            {
                XUART_receive();
                uartReadDataReg.readCount = XUART_receiveByteCount();
            }
            else if( regs->mode == 2 )
            {
                XUART_readThenWrite();
                uartReadDataReg.readCount = XUART_receiveByteCount();
            }
            else if( regs->mode == 3 )
            {
                XUART_writeThenRead();
                uartReadDataReg.readCount = XUART_receiveByteCount();
            }
        }
    }
}

void uartReadDataRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sUartReadDataReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {
        regs->readCount = XUART_receiveByteCount();
        regs->byte = XUART_rxBufferReadByte(regs->index);
    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        
    }
}

void uartWriteDataRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sUartWriteDataReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {

    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        XUART_txBufferWriteByte(regs->index, regs->byte);
    }
}

/* ========== I2C control ========== */

extern int XI2C_setBitRate(int bitRate);
extern int XI2C_setTxCount(int count);
extern int XI2C_setRxCount(int count);
extern int XI2C_setTargetAddress(int address);
extern int XI2C_txBufferWriteByte(int index, int byte);
extern int XI2C_rxBufferReadByte(int index);
extern int XI2C_setTransferTimeout(int timeout);
extern int XI2C_transfer();

struct sI2CTransferConfigReg i2cTransferConfigReg;
struct sI2CControlReg i2cControlReg;
struct sI2CReadDataReg i2cReadDataReg;
struct sI2CWriteDataReg i2cWriteDataReg;


void i2cControlRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sI2CControlReg* regs = reg;
    
    if( operation == SSCP_REGISTER_OPERATION_READ )
    {

    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        XI2C_setBitRate(regs->fastModeEnable);
        XI2C_setTargetAddress(regs->targetAddress);
        XI2C_setTransferTimeout(regs->timeout * 1000);
    }
}

int i2cTransferStatus = 0;
extern pthread_mutex_t i2cMutex;

void i2cTransferConfigRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sI2CTransferConfigReg* regs = reg;
    
    if( operation == SSCP_REGISTER_OPERATION_READ )
    {
        regs->status = i2cTransferStatus;
    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        XI2C_setRxCount(regs->readSize);
        XI2C_setTxCount(regs->writeSize);
        
        if( regs->transfer )
        {
            pthread_mutex_lock(&i2cMutex);
            if( XI2C_transfer() < 0 )
            {
                i2cTransferStatus = 1;
            }
            else
            {
                i2cTransferStatus = 0;
            }
            pthread_mutex_unlock(&i2cMutex);
        }
    }
}

void i2cReadDataRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sI2CReadDataReg* regs = reg;
    
    if( operation == SSCP_REGISTER_OPERATION_READ )
    {
        regs->byte = XI2C_rxBufferReadByte(regs->index);
    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
       
    }
}

void i2cWriteDataRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    struct sI2CWriteDataReg* regs = reg;
    
    if( operation == SSCP_REGISTER_OPERATION_READ )
    {

    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        XI2C_txBufferWriteByte(regs->index, regs->byte);        
    }
}

/**
 * ======== DAC control and configuration ========
 */

struct sDacControlReg dacControlReg;

extern void dacSetOutputVoltage(int index, int voltage);

void dacControlRegCallback(void* reg, int operation)
{
    struct sDacControlReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        dacSetOutputVoltage( regs->index, (int)((int16_t)regs->voltage) );
    }
}

/**
 * ========== High speed ADC control and data ==========
 */

struct sHsAdcControlReg hsAdcControlReg;

extern void hsadc_start(int sample_count, int mode);
extern int hsadc_readSample(int channel, int index);
extern bool hsadc_isPending();

void hsadcControlRegCallback(void* reg, int operation)
{
    struct sHsAdcControlReg* regs = reg;

    if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        if( regs->start )
        {
            hsadc_start( regs->numberOfSamples, regs->dualMode );

            while( hsadc_isPending() == true );
        }
    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {

    }
}

struct sHsAdcSamplesReg hsAdcSamplesReg;

void hsadcSamplesRegCallback(void* reg, int operation)
{
    struct sHsAdcSamplesReg* regs = reg;

    uint32_t result;
    int sample;

    result = 0;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {
        sample = hsadc_readSample(regs->channel, regs->index);
       
        if( sample < 0 )
        {
            regs->sample = (uint16_t)(-sample);
        }
        else
        {
            regs->sample = sample;
        }
    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {

    }
}