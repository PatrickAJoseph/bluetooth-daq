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
#include <errno.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
#include <ti/drivers/SPI.h>
// #include <ti/drivers/Watchdog.h>
#include <ti/devices/cc23x0r5/driverlib/hapi.h>

/* Driver configuration */
#include "ti_drivers_config.h"


SPI_Params spiParams;
SPI_Handle spiHandle;
SPI_Transaction spiTransaction;
uint16_t spiTransferWordU16;

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

    if( ret )
    {
        __asm volatile("bkpt 0");
    }

    int index;

    passCount = 0;
    failCount = 0;

    while (1)
    {
        for( index = 0 ; index <= 0xFFFFU ; index++ )
        {
            DIO_writeOutput((uint16_t)index);

            ret = DIO_readInput();

            if( ret < 0 )
            {
                __asm volatile("bkpt 0");
            }

            input = (uint16_t)ret;

            if( input != (uint16_t)index )
            {
                __asm volatile("bkpt 0");
                failCount++;
            }
            else
            {
                passCount++;
            }
        }

        __asm volatile("bkpt 0");
    }
}
