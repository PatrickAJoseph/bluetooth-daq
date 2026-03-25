/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== empty.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/UART2.h>
// #include <ti/drivers/Watchdog.h>
#include <ti/devices/cc23x0r5/driverlib/hapi.h>

/* Driver configuration */
#include "ti_drivers_config.h"


SPI_Params spiParams;
SPI_Handle spiHandle;
SPI_Transaction spiTransaction;
uint16_t spiTransferWordU16;

#define XSPI_MAX_TRANSFER_SIZE      64

SPI_Params xspiParams;
uint8_t xspiTxBuffer[XSPI_MAX_TRANSFER_SIZE];
uint8_t xspiRxBuffer[XSPI_MAX_TRANSFER_SIZE];
size_t xspiTransferSize;
unsigned int xspiChipSelectPolarity;

UART2_Params xuartParams;
UART2_Handle uartHandle;

#define XUART_MAX_TRANSFER_SIZE     32

uint8_t xuartTxBuffer[XUART_MAX_TRANSFER_SIZE];
uint8_t xuartRxBuffer[XUART_MAX_TRANSFER_SIZE];
size_t xuartWriteSize;
size_t xuartReadSize;

#define XI2C_MAX_TRANSFER_SIZE      32

I2C_Handle i2cHandle;
I2C_Params i2cParams;
I2C_Transaction i2cTransaction;

uint8_t i2cTxBuffer[XI2C_MAX_TRANSFER_SIZE];
uint8_t i2cRxBuffer[XI2C_MAX_TRANSFER_SIZE];

/* ======================================= External SPI API. ====================================== */

int XSPI_init()
{
    if( spiHandle == NULL )
    {
        SPI_Params_init(&xspiParams);

        xspiParams.bitRate = 1000000;
        xspiParams.dataSize = 8;
        xspiParams.mode = SPI_CONTROLLER;
        xspiParams.transferMode = SPI_MODE_BLOCKING;
        xspiParams.frameFormat = SPI_POL0_PHA0;
    
        spiHandle = SPI_open(CONFIG_SPI, &spiParams);
    }

    if( spiHandle == NULL )
    {
        return -EIO;
    }

    GPIO_write(CONFIG_XSPI_SEL,1);

    xspiTransferSize = 0;

    memset( xspiTxBuffer , 0, XSPI_MAX_TRANSFER_SIZE );
    memset( xspiRxBuffer, 0, XSPI_MAX_TRANSFER_SIZE );

    return 0;
}

int XSPI_setBitRate(int bitRate)
{
    xspiParams.bitRate = bitRate;
    return 0;
}

int XSPI_setFrameFormat(SPI_FrameFormat frameFormat)
{
    xspiParams.frameFormat = frameFormat;
    return 0;
}

int XSPI_setTransferSize(size_t size)
{
    if( size > XSPI_MAX_TRANSFER_SIZE )
    {
        return -EINVAL;
    }

    xspiTransferSize = size;
    return 0;
}

int XSPI_txBufferWriteByte(int index, uint8_t byte)
{
    if( index >= xspiTransferSize )
    {
        return -EINVAL;
    }

    xspiTxBuffer[index] = byte;

    return 0;
}

int XSPI_rxBufferReadByte(int index, uint8_t byte)
{
    if( index >= xspiTransferSize )
    {
        return -EINVAL;
    }

    return (int)xspiRxBuffer[index];
}

void XSPI_setChipSelectPolarity(unsigned int polarity)
{
    xspiChipSelectPolarity = polarity;
}

int XSPI_transfer()
{
    unsigned int xspiPolarity;

    xspiPolarity = xspiChipSelectPolarity;

    xspiParams.dataSize = 8;
    xspiParams.mode = SPI_CONTROLLER;
    xspiParams.transferMode = SPI_MODE_BLOCKING;
    xspiParams.transferTimeout = SPI_WAIT_FOREVER;
    xspiParams.transferCallbackFxn = NULL;
    xspiParams.custom = NULL;
    
    if( spiHandle != NULL )
        SPI_close(spiHandle);

    spiHandle = SPI_open(CONFIG_SPI, &xspiParams);
    
    if( spiHandle == NULL )
    {
        return -EIO;
    }

    spiTransaction.rxBuf = xspiRxBuffer;
    spiTransaction.txBuf = xspiTxBuffer;
    spiTransaction.count = xspiTransferSize;
    
    if( xspiPolarity )
    {
        GPIO_write(CONFIG_XSPI_SEL, 1 );
    }
    else
    {
        GPIO_write(CONFIG_XSPI_SEL , 0);
    }

    if( SPI_transfer( spiHandle, &spiTransaction ) == false )
    {
        if( xspiPolarity )
        {
            GPIO_write(CONFIG_XSPI_SEL, 0);
        }
        else
        {
            GPIO_write(CONFIG_XSPI_SEL, 1);
        }
        
        return -EIO;
    }

    if( xspiPolarity )
    {
        GPIO_write(CONFIG_XSPI_SEL, 0);
    }
    else
    {
        GPIO_write(CONFIG_XSPI_SEL, 1);
    }

    return 0;
}

/* ============================ External UART API functions. ===================================== */

int XUART_init()
{
    if( uartHandle == NULL )
    {
        UART2_Params_init(&xuartParams);

        xuartParams.baudRate = 9600;
        xuartParams.readMode = UART2_Mode_BLOCKING;
        xuartParams.writeMode = UART2_Mode_BLOCKING; 

        uartHandle = UART2_open(CONFIG_UART, &xuartParams);
    }

    return 0;
}

void XUART_setBaudRate(int baudRate)
{
    xuartParams.baudRate = baudRate;
}

void XUART_setParity(UART2_Parity parity)
{
    xuartParams.parityType = parity;
}

void XUART_setStopBits(UART2_StopBits stopBits)
{
    xuartParams.stopBits = stopBits;
}

int XUART_txBufferWriteByte(int index, uint8_t byte)
{
    if( index >= XUART_MAX_TRANSFER_SIZE )
    {
        return -EINVAL;
    }

    xuartTxBuffer[index] = byte;

    return 0;
}

int XUART_rxBufferReadByte(int index)
{
    if( index >= XUART_MAX_TRANSFER_SIZE )
    {
        return -EINVAL;   
    }

    return xuartRxBuffer[index];
}

int XUART_setWriteSize(size_t size)
{
    if( size > XUART_MAX_TRANSFER_SIZE )
    {
        return -EINVAL;
    }

    xuartWriteSize = size;

    return 0;
}

int XUART_setReadSize(size_t size)
{
    if( size > XUART_MAX_TRANSFER_SIZE )
    {
        return -EINVAL;
    }

    xuartReadSize = size;

    return 0;
}

int XUART_getRxCount()
{
    int ret;

    ret = UART2_getRxCount(uartHandle);

    return ret;
}

int xuartReceiveTimeout;

int XUART_setReceiveTimeout(int timeout)
{
    xuartReceiveTimeout = timeout;
    return 0;
}

int xuartReceiveByteCount;

int XUART_receiveByteCount()
{
    return xuartReceiveByteCount;
}

int xuartReceiveTimeoutStatus = 0;

int XUART_receiveTimeoutStatus()
{
    return xuartReceiveTimeoutStatus;
}

int XUART_transmit()
{
    // UART peripheral of MCU is shared between the RS-485 interface
    // and the external UART (XUART) interface. So, we have to close
    // the existing connection and open up a new one.

    if( uartHandle != NULL )
    {
        UART2_close(uartHandle);
    }

    uartHandle = UART2_open(CONFIG_UART, &xuartParams);

    if( uartHandle == NULL )
    {
        return -EIO;
    }

    GPIO_write(CONFIG_UART_SEL, 1);
    UART2_write( uartHandle, xuartTxBuffer, xuartWriteSize, NULL);
    GPIO_write(CONFIG_UART_SEL, 0);

    // TODO: We will have to restore the RS-485 interface setting back over here.

    return 0;
}

int XUART_receive()
{
    int_fast16_t ret;

    // UART peripheral of MCU is shared between the RS-485 interface
    // and the external UART (XUART) interface. So, we have to close
    // the existing connection and open up a new one.

    if( uartHandle != NULL )
    {
        UART2_close(uartHandle);
    }

    uartHandle = UART2_open(CONFIG_UART, &xuartParams);

    if( uartHandle == NULL )
    {
        return -EIO;
    }

    UART2_rxEnable(uartHandle);

    GPIO_write(CONFIG_UART_SEL, 1);
    //sleep(5)
    ret = UART2_readTimeout( uartHandle, xuartRxBuffer, xuartReadSize, (size_t*)&xuartReceiveByteCount , xuartReceiveTimeout );
    GPIO_write(CONFIG_UART_SEL, 0);

    UART2_rxDisable(uartHandle);

    // TODO: We will have to restore the RS-485 interface setting back over here.

    if( ret == UART2_STATUS_ETIMEOUT )
    {
        xuartReceiveTimeoutStatus = 1;
        return -ETIME;
    }

    xuartReceiveTimeoutStatus = 0;

    return 0;
}

/* ============================ Digital input output API functions. ============================== */

int DIO_init()
{
    SPI_Params_init(&spiParams);

    spiParams.bitRate = 1000000;
    spiParams.dataSize = 8;
    spiParams.mode = SPI_CONTROLLER;
    spiParams.transferMode = SPI_MODE_BLOCKING;
    spiParams.frameFormat = SPI_POL0_PHA0;
    
    spiHandle = SPI_open(CONFIG_SPI, &spiParams);

    if( spiHandle == NULL )
    {
        return -EIO;
    }

    return 0;
}

int DIO_writeOutput(uint16_t word)
{
    int ret;

    if(spiHandle == NULL)
    {
        return -EBUSY;
    }

    spiTransferWordU16 = ( ( word & 0xFF00U ) >> 8 ) | ( ( word & 0x00FFU ) << 8 );

    spiTransaction.count = 2;
    spiTransaction.txBuf = (void*)&spiTransferWordU16;
    spiTransaction.rxBuf = NULL;

    GPIO_write(CONFIG_DOUT_LOAD, 0);

    ret = SPI_transfer( spiHandle, &spiTransaction );

    GPIO_write(CONFIG_DOUT_LOAD, 1);

    if( !ret )
    {
        return -EIO;
    }

    return 0;
}

int DIO_readInput()
{
    int ret;

    if(spiHandle == NULL)
    {
        return -EBUSY;
    }

    spiTransaction.count = 2;
    spiTransaction.rxBuf = (void*)&spiTransferWordU16;
    spiTransaction.txBuf = NULL;

    GPIO_write(CONFIG_DIN_LOAD, 0);
    HapiWaitUs(2);
    GPIO_write(CONFIG_DIN_LOAD, 1);
    HapiWaitUs(2);

    ret = SPI_transfer( spiHandle, &spiTransaction );

    spiTransferWordU16 = ( ( spiTransferWordU16 & 0xFF00U ) >> 8 ) | ( ( spiTransferWordU16 & 0x00FFU ) << 8 ); 

    if( ret == false )
    {
        return -EIO;
    }

    return (int)spiTransferWordU16;
}

/* =========== External I2C API functions ========== */

int XI2C_init()
{
    if( i2cHandle == NULL )
    {
        I2C_Params_init(&i2cParams);

        i2cHandle = I2C_open(CONFIG_I2C_0, &i2cParams);
    }

    GPIO_write(CONFIG_I2C_SEL, 1);

    if( i2cHandle == NULL )
    {
        GPIO_write(CONFIG_I2C_SEL, 1);
        return -EIO;
    }

    return 0;
}

int XI2C_setTxCount(int count)
{
    i2cTransaction.writeCount = count;
    return 0;
}

int XI2C_setRxCount(int count)
{
    i2cTransaction.readCount = count;
    return 0;
}

int XI2C_setTargetAddress(int address)
{
    i2cTransaction.targetAddress = address;
    return 0;
}

int XI2C_txBufferWriteByte(int index, uint8_t byte)
{
    i2cTxBuffer[index] = byte;
}

int XI2C_rxBufferReadByte(int index)
{
    return (int)i2cRxBuffer[index];
}

int XI2C_transfer()
{
    int ret;

    //i2cTransaction.targetAddress = 0x3C;
    i2cTransaction.readBuf = i2cRxBuffer;
    i2cTransaction.writeBuf = i2cTxBuffer;
    //i2cTransaction.readCount = 2;
    //i2cTransaction.writeCount = 2;
    
    ret = I2C_transferTimeout(i2cHandle, &i2cTransaction, 1000000);

    if( ret < 0 )
    {
        return -ETIME;
    }

    return 0;
}

/* ========== RS485 interface API =========== */

int RS485_init()
{
   UART2_Params params;

   if( uartHandle != NULL )
   {
        UART2_close(uartHandle);
   }

    UART2_Params_init(&params);

    uartHandle = UART2_open(CONFIG_UART, &params);

   if( uartHandle == NULL )
   {
    return -EIO;
   }

   return 0;
}

int RS485_write(uint8_t* buffer, size_t size)
{
    if( uartHandle != NULL )
    {
        RS485_init();
        GPIO_write(CONFIG_UART_SEL, 0);
    }

    GPIO_write(CONFIG_XCVR_DRV_EN, 1);
    UART2_write(uartHandle, buffer, size, NULL);
    GPIO_write(CONFIG_XCVR_DRV_EN,0);
}

int RS485_read(uint8_t* buffer, size_t size)
{
    if( uartHandle != NULL )
    {
        RS485_init();
        GPIO_write(CONFIG_UART_SEL, 0);
    }

    GPIO_write(CONFIG_UART_SEL, 0);
    GPIO_write(CONFIG_XCVR_DRV_EN,0);

    UART2_rxEnable(uartHandle);
    UART2_read(uartHandle, buffer, size, NULL);
    UART2_rxDisable(uartHandle);
}


/*
 *  ======== mainThread ========
 */

uint16_t input;
int passCount;
int failCount;

uint8_t rs485Test[] = { 'T', 'e', 's', 't', '\r', '\n' };

void *mainThread(void *arg0)
{
    int ret;

    GPIO_init();
    I2C_init();
    SPI_init();
    RS485_init();

    while (1)
    {
        RS485_read( rs485Test, 6 );
        sleep(0.1);
    }
}
