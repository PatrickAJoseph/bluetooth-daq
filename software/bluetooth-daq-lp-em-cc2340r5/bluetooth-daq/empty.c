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

/*
 *  ======== mainThread ========
 */

uint16_t input;
int passCount;
int failCount;

void *mainThread(void *arg0)
{
    int ret;

    GPIO_init();
    I2C_init();
    SPI_init();

    ret = DIO_init();

    if( ret < 0 )
    {
        __asm volatile("bkpt 0");
    }

    ret = XSPI_init();

    XSPI_setBitRate(2000000);
    XSPI_setFrameFormat(SPI_POL1_PHA1);
    XSPI_setTransferSize(XSPI_MAX_TRANSFER_SIZE);
    XSPI_setChipSelectPolarity(1);

    XUART_init();
    XUART_setBaudRate(115200);
    //XUART_setParity(UART2_Parity_NONE);
    //XUART_setStopBits(UART2_StopBits_1);
    XUART_setReadSize(4);
    XUART_setWriteSize(4);

    XUART_txBufferWriteByte(0, 'a');
    XUART_txBufferWriteByte(1, 'b');
    XUART_txBufferWriteByte(2, 'c');
    XUART_txBufferWriteByte(3, 'd');

    XUART_setReceiveTimeout(5000000);
    XUART_setReadSize(8);
    
    while (1)
    {
        //ret = XUART_transmit();

        //if( ret < 0 )
        //{
        //    __asm volatile("bkpt 0");
        //}

        (void)XUART_receive();

        sleep(0.1);
    }
}
