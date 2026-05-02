
#include <ti/drivers/I2C.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/GPIO.h>
#include <ti/devices/cc23x0r5/driverlib/hapi.h>

#include <ti/posix/ticlang/sys/types.h>

extern int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
extern int pthread_mutex_lock(pthread_mutex_t *mutex);
extern int pthread_mutex_unlock(pthread_mutex_t *mutex);

#include "ti_drivers_config.h"

#define MUX_INPUT_0             0
#define MUX_INPUT_1             1
#define MUX_INPUT_2             2
#define MUX_INPUT_3             3
#define MUX_INPUT_4             4
#define MUX_INPUT_5             5
#define MUX_INPUT_6             6
#define MUX_INPUT_7             7

#define MUX_SELECT(x)                                   \
do{                                                     \
    GPIO_write(CONFIG_MUX2, (x & 1) ? true : false );   \
    GPIO_write(CONFIG_MUX1, (x & 2) ? true : false );   \
    GPIO_write(CONFIG_MUX0, (x & 4) ? true : false );   \
}while(0);                                              \

#define DAC_MUX_SELECT(x)                               \
do{                                                     \
    GPIO_write(CONFIG_MUX2, (x & 1) ? false : true );   \
    GPIO_write(CONFIG_MUX1, (x & 2) ? false : true );   \
    GPIO_write(CONFIG_MUX0, (x & 4) ? false : true );   \
}while(0);                                              \

#define SDADC_DISABLE()                                 \
    GPIO_write(CONFIG_SDADCDIS, true);                  \

#define SDADC_ENABLE()                                  \
    GPIO_write(CONFIG_SDADCDIS, false);                 \

#define DAC_ENABLE()                                    \
    GPIO_write(CONFIG_DACEN, true);                    \

#define DAC_DISABLE()                                   \
    GPIO_write(CONFIG_DACEN, false);                     \

extern void xdac_writeOutput(uint16_t x);

#define XDAC_SET_OUTPUT(x)                               \
do{                                                     \
    xdac_writeOutput(x);                                \
}while(0);

int dacSingleEndedOutputGain[8] = { 
                                    [0] = 35778, 
                                    [1] = 35714, 
                                    [2] = 35778, 
                                    [3] = 35778, 
                                    [4] = 36363,
                                    [5] = 36496,
                                    [6] = 36496, 
                                    [7] = 36496,
                                  };

int dacSingleEndedOutputOffset[8] = { 
                                        [0] = 161325371, 
                                        [1] = 161428572, 
                                        [2] = 161896244, 
                                        [3] = 161180680, 
                                        [4] = 166181819, 
                                        [5] = 166423358, 
                                        [6] = 166423358, 
                                        [7] = 165328468,
                                    };

#define DAC_SET_SINGLE_ENDED_OUTPUT(channel, x)                  \
do                                                      \
{                                                       \
    int result;                                         \
                                                                                        \
    result = ( dacSingleEndedOutputGain[7-channel] * x - dacSingleEndedOutputOffset[7-channel] ) / 100000;     \
                                        \
    XDAC_SET_OUTPUT(result);            \
                                        \
}while(0);

static inline void dac_setSingleEndedOutputVoltage(int channel, int voltage)
{
    DAC_SET_SINGLE_ENDED_OUTPUT(channel, voltage);
}

static inline void dac_muxSelect(int x)
{
    DAC_MUX_SELECT(x);
}

static inline void dac_setCode(int x)
{
    XDAC_SET_OUTPUT(x);
}

uint8_t xadcSpiTxBuffer[16];
uint8_t xadcSpiRxBuffer[16];

extern SPI_Handle spiHandle;
SPI_Params xadcSpiParams;
SPI_Transaction xadcSpiTransaction;

static void xadc_init(void)
{
    int ret;

    if (spiHandle != NULL)
    {
        SPI_close(spiHandle);
    }

    SPI_Params_init(&xadcSpiParams);

    xadcSpiParams.frameFormat = SPI_POL0_PHA1;   // SPI Mode 1
    xadcSpiParams.bitRate     = 100000;         // 1 MHz

    spiHandle = SPI_open(CONFIG_SPI, &xadcSpiParams);

    if (spiHandle == NULL)
    {
        __asm volatile("bkpt 0");
    }

    xadcSpiTransaction.txBuf = xadcSpiTxBuffer;
    xadcSpiTransaction.rxBuf = xadcSpiRxBuffer;
    xadcSpiTransaction.count = 12;   // 4 words x 24 bits = 12 bytes

    memset(xadcSpiTxBuffer, 0, sizeof(xadcSpiTxBuffer));
    memset(xadcSpiRxBuffer, 0, sizeof(xadcSpiRxBuffer));

    GPIO_write(CONFIG_ADCCS, true);

    /****************************************
     * Transaction 1: RESET command
     * 00 11 00 00 00 00 00 00 00 00 00 00
     ****************************************/

    memset(xadcSpiTxBuffer, 0, 12);

    xadcSpiTxBuffer[0] = 0x00;
    xadcSpiTxBuffer[1] = 0x11;
    xadcSpiTxBuffer[2] = 0x00;

    GPIO_write(CONFIG_ADCCS, false);

    ret = SPI_transfer(spiHandle, &xadcSpiTransaction);

    GPIO_write(CONFIG_ADCCS, true);

    if (!ret)
    {
        __asm volatile("bkpt 0");
    }

    HapiWaitUs(250);

    /****************************************
     * Transaction 2: UNLOCK command
     * 06 55 00 00 00 00 00 00 00 00 00 00
     ****************************************/

    memset(xadcSpiTxBuffer, 0, 12);

    xadcSpiTxBuffer[0] = 0x06;
    xadcSpiTxBuffer[1] = 0x55;
    xadcSpiTxBuffer[2] = 0x00;

    GPIO_write(CONFIG_ADCCS, false);

    ret = SPI_transfer(spiHandle, &xadcSpiTransaction);

    GPIO_write(CONFIG_ADCCS, true);

    if (!ret)
    {
        __asm volatile("bkpt 0");
    }

    HapiWaitUs(250);
}

static bool isInitialized = false;

int dacVoltage[4] = { [0] = 0, [1] = 0 , [2] = 0, [3] = 0 };

void dacSetOutputVoltage(int index, int voltage)
{
    dacVoltage[index] = voltage;
}

bool dacTestModeEnable = false;
extern bool isI2cBusy;

static void dacHandler()
{
    static int dacChannel = 0;
    static int pole = 0;
    static int counter = 0;

    if( counter >= 10 )
    {
        counter = 0;

    if( dacVoltage[dacChannel] < 0 )
    {
        if( pole == 0 )
        {
            DAC_DISABLE();
            dac_muxSelect(7- 2*dacChannel);
            dac_setSingleEndedOutputVoltage(7- 2*dacChannel, 5000);
            DAC_ENABLE();
            pole = 1;
        }
        else {
            DAC_DISABLE();
            dac_muxSelect(6 - 2*dacChannel);
            dac_setSingleEndedOutputVoltage(6- 2*dacChannel, 5000 - dacVoltage[dacChannel]);
            DAC_ENABLE();
            pole = 0;

            dacChannel++;
        }
    }
    else
    {
        if( pole == 0 )
        {
            DAC_DISABLE();
            dac_muxSelect(6- 2*dacChannel);
            dac_setSingleEndedOutputVoltage(6- 2*dacChannel, 5000);
            DAC_ENABLE();

            pole = 1;
        }
        else
        {
            DAC_DISABLE();
            dac_muxSelect(7- 2*dacChannel);
            dac_setSingleEndedOutputVoltage(7- 2*dacChannel, 5000 + dacVoltage[dacChannel]);
            DAC_ENABLE();

            pole = 0;

            dacChannel++;
        }
    }

    if( dacChannel >= 4 )
    {
        dacChannel = 0;
    }
    }

    counter++;
}

int dacTestMode_channelCode[8] = {0};

void dacTestMode_setChannelCode(int index, int code)
{
    dacTestMode_channelCode[index] = code;
}

void dacTestModeHandler()
{
    static int counter = 0;
    static int channel = 0;

    counter++;

    if( counter == 10 )
    {
        counter = 0;

        DAC_DISABLE();
        dac_muxSelect(7 - channel);
        dac_setCode(dacTestMode_channelCode[channel]);
        DAC_ENABLE();

        channel++;

        if( channel == 8 )
        {
            channel = 0;
        }
    }
}

void analogSubmodule_init()
{
    MUX_SELECT(MUX_INPUT_0);
    SDADC_ENABLE();
    DAC_ENABLE();
}

extern pthread_mutex_t i2cMutex;

void analogIsrSection()
{
    if( !isInitialized )
    {
        analogSubmodule_init();
        isInitialized = true;
    }
    else
    {
        if( dacTestModeEnable == false )
        {
            pthread_mutex_lock(&i2cMutex);
            dacHandler();
            pthread_mutex_unlock(&i2cMutex);
        }
        else
        {
            pthread_mutex_lock(&i2cMutex);
            dacTestModeHandler();
            pthread_mutex_unlock(&i2cMutex);
        }
    }
}

