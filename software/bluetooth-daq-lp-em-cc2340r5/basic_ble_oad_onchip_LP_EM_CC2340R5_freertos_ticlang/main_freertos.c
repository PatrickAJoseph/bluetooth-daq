/******************************************************************************

 @file  main_freertos.c

 @brief main entry of the BLE stack sample application.

 Group: WCS, BTS
 Target Device: cc23xx

 ******************************************************************************
 
 Copyright (c) 2013-2025, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.


 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 
 
 *****************************************************************************/

/*******************************************************************************
 * INCLUDES
 */

/* RTOS header files */
#include <FreeRTOS.h>
#include <stdint.h>
#include <task.h>
#include <pthread.h>
#include <semaphore.h>

#include <ti/posix/ticlang/sys/types.h>

extern int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
extern int pthread_mutex_lock(pthread_mutex_t *mutex);
extern int pthread_mutex_unlock(pthread_mutex_t *mutex);


#ifdef __ICCARM__
    #include <DLib_Threads.h>
#endif
#include <ti/drivers/Power.h>
#include <ti/devices/DeviceFamily.h>
#include <ti/drivers/timer/LGPTimerLPF3.h>

#include "ti/ble/stack_util/icall/app/icall.h"
#include "ti/ble/stack_util/health_toolkit/assert.h"
#include "ti/ble/stack_util/bcomdef.h"

#ifndef USE_DEFAULT_USER_CFG
#include "ti/ble/app_util/config/ble_user_config.h"
#include <ti/devices/cc23x0r5/driverlib/hapi.h>

#include <ti/drivers/ADC.h>

// BLE user defined configuration
icall_userCfg_t user0Cfg = BLE_USER_CFG;
#endif // USE_DEFAULT_USER_CFG



/*******************************************************************************
 * MACROS
 */

/*******************************************************************************
 * CONSTANTS
 */

/*******************************************************************************
 * TYPEDEFS
 */

/*******************************************************************************
 * LOCAL VARIABLES
 */

/*******************************************************************************
 * GLOBAL VARIABLES
 */

/*******************************************************************************
 * EXTERNS
 */
extern void appMain(void);
extern void AssertHandler(uint8 assertCause, uint8 assertSubcause);

/*******************************************************************************
 * @fn          Main
 *
 * @brief       Application Main
 *
 * input parameters
 *
 * @param       None.
 *
 * output parameters
 *
 * @param       None.
 *
 * @return      None.
 */

LGPTimerLPF3_Handle timerHandle;
LGPTimerLPF3_Params timerParams;
sem_t timerSem;
int timerIsrCount;

static void timer_callback(LGPTimerLPF3_Handle handle, LGPTimerLPF3_IntMask interruptMask)
{
    sem_post(&timerSem);
}

void timer_init()
{
    uint32_t counterTarget;
    int ret;

    LGPTimerLPF3_Params_init(&timerParams);
    timerParams.hwiCallbackFxn = timer_callback;

    timerHandle = LGPTimerLPF3_open(CONFIG_LGPTIMER_0, &timerParams);

    if(timerHandle == NULL)
    {
        __asm volatile("bkpt 0");
    }

    // Set counter target
    counterTarget = 480000 - 1;  // 10 ms with a system clock of 48 MHz
    LGPTimerLPF3_setInitialCounterTarget(timerHandle, counterTarget, true);

    // Enable counter target interrupt
    LGPTimerLPF3_enableInterrupt(timerHandle, LGPTimerLPF3_INT_TGT);

    ret = sem_init(&timerSem, 0, 1);

    // Start counter in count-up-periodic mode
    LGPTimerLPF3_start(timerHandle, LGPTimerLPF3_CTL_MODE_UP_PER);    
}


ADC_Handle adc1Handle;
ADC_Handle adc2Handle;

ADC_Params adcParams;

void hsadc_init()
{
  ADC_init();

  ADC_Params_init(&adcParams);

  adc1Handle = ADC_open(CONFIG_ADC_0, &adcParams);
  adc2Handle = ADC_open(CONFIG_ADC_1, &adcParams);    
}


LGPTimerLPF3_Handle hsadcTimerHandle;

#define HSADC_MAX_SAMPLE_COUNT  512

volatile int hsadc_currentSampleCount = 0;
volatile int hsadc_targetSampleCount = 0;
volatile int hsadc_currentChannel = 0;
volatile int hsadc_dualChannelMode = 0;
volatile int hsadc_singleModeChannel = 0;

volatile uint16_t hsadc_channel1Samples[HSADC_MAX_SAMPLE_COUNT];
volatile uint16_t hsadc_channel2Samples[HSADC_MAX_SAMPLE_COUNT];

static void hsadctimer_callback(LGPTimerLPF3_Handle handle, LGPTimerLPF3_IntMask interruptMask)
{
    if( hsadc_dualChannelMode == 0 )
    {
        ADC_convert(adc1Handle, &hsadc_channel1Samples[hsadc_currentSampleCount]);

        hsadc_currentSampleCount++;
    }
    else 
    {
        if( hsadc_currentChannel == 0 )
        {
            ADC_convert(adc1Handle, &hsadc_channel1Samples[hsadc_currentSampleCount]);
            hsadc_currentChannel = 1;
        }
        else
        {
            ADC_convert(adc2Handle, &hsadc_channel2Samples[hsadc_currentSampleCount]);
            hsadc_currentChannel = 0;
            hsadc_currentSampleCount++;
        }
    }

    if( hsadc_currentSampleCount == hsadc_targetSampleCount )
    {
        LGPTimerLPF3_stop(hsadcTimerHandle);
    }
}

void hsadcTimer_init()
{
    uint32_t counterTarget;
    int ret;

    LGPTimerLPF3_Params_init(&timerParams);
    timerParams.hwiCallbackFxn = hsadctimer_callback;

    hsadcTimerHandle = LGPTimerLPF3_open(CONFIG_LGPTIMER_1, &timerParams);

    if(hsadcTimerHandle == NULL)
    {
        __asm volatile("bkpt 0");
    }

    // Set counter target
    counterTarget = 960 - 1;  // 50 us with a system clock of 48 MHz
    LGPTimerLPF3_setInitialCounterTarget(hsadcTimerHandle, counterTarget, true);
}

void hsadc_start(int sample_count, int mode)
{
    hsadc_targetSampleCount = sample_count;
    hsadc_dualChannelMode = mode;
    hsadc_currentSampleCount = 0;

    // Enable counter target interrupt
    LGPTimerLPF3_enableInterrupt(hsadcTimerHandle, LGPTimerLPF3_INT_TGT);

    // Start counter in count-up-periodic mode
    LGPTimerLPF3_start(hsadcTimerHandle, LGPTimerLPF3_CTL_MODE_UP_PER);    
}

int hsadc_convertToMillivolts(int raw)
{
    int temp;

    temp = 114*raw -89695;

    return (int)temp;
}

int hsadc_readSample(int channel, int index)
{
    if( channel == 0 )
    {
        return ( hsadc_convertToMillivolts(hsadc_channel1Samples[index]) );
    }

    return hsadc_channel2Samples[index];
}

bool hsadc_isPending()
{
    return (hsadc_currentSampleCount < hsadc_targetSampleCount );
}

extern void sscpRS485Process();
extern void sscpBleProcess();

void* sscpProcessingTask(void* args)
{
    while(1) {
        sscpRS485Process();
        sscpBleProcess();
        usleep(1000);
    }
}

extern void analogIsrSection();

void* isrTask(void* args)
{
    while(1)
    {
        sem_wait(&timerSem);
        analogIsrSection();
    }
}

pthread_mutex_t spiMutex;
pthread_mutex_t i2cMutex;

int main()
{
  /* Register Application callback to trap asserts raised in the Stack */
  halAssertCback = AssertHandler;
  RegisterAssertCback(AssertHandler);

  Board_init();

  hsadc_init();

  /* Update User Configuration of the stack */
  user0Cfg.appServiceInfo->timerTickPeriod = ICall_getTickPeriod();
  user0Cfg.appServiceInfo->timerMaxMillisecond  = ICall_getMaxMSecs();

  /* Initialize all applications tasks */
  appMain();

  //hsadc_init();
  hsadcTimer_init();
  timer_init();


 HapiWaitUs(10000);

  extern void digitalSubmodule_init();
  digitalSubmodule_init();

  pthread_mutex_init(&i2cMutex, NULL);
  pthread_mutex_init(&spiMutex, NULL);

  pthread_t thread;
  pthread_attr_t attrs;
  struct sched_param priParam;
  int retc;

  /* Initialize the attributes structure with default values */
  pthread_attr_init(&attrs);

  /* Set priority, detach state, and stack size attributes */
  priParam.sched_priority = 3;
  retc                    = pthread_attr_setschedparam(&attrs, &priParam);
  retc |= pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
  retc |= pthread_attr_setstacksize(&attrs, 2048);
  if (retc != 0)
  {
    /* failed to set attributes */
    while (1) {}
  }

  retc = pthread_create(&thread, &attrs, sscpProcessingTask, NULL);

  if (retc != 0)
  {
    /* pthread_create() failed */
    while (1) {}
  }

  /* Initialize the attributes structure with default values */
  pthread_attr_init(&attrs);

  /* Set priority, detach state, and stack size attributes */
  priParam.sched_priority = 1;
  retc                    = pthread_attr_setschedparam(&attrs, &priParam);
  retc |= pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
  retc |= pthread_attr_setstacksize(&attrs, 1024);
  if (retc != 0)
  {
    /* failed to set attributes */
    while (1) {}
  }

  retc = pthread_create(&thread, &attrs, isrTask, NULL);

  if (retc != 0)
  {
    /* pthread_create() failed */
    while (1) {}
  }


  /* Start the FreeRTOS scheduler */
  vTaskStartScheduler();

  return 0;

}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    AssertHandler(HAL_ASSERT_CAUSE_STACK_OVERFLOW_ERROR, 0);
}

/*******************************************************************************
 * @fn          AssertHandler
 *
 * @brief       This is the Application's callback handler for asserts raised
 *              in the stack.  When EXT_HAL_ASSERT is defined in the Stack Wrapper
 *              project this function will be called when an assert is raised,
 *              and can be used to observe or trap a violation from expected
 *              behavior.
 *
 *              As an example, for Heap allocation failures the Stack will raise
 *              HAL_ASSERT_CAUSE_OUT_OF_MEMORY as the assertCause and
 *              HAL_ASSERT_SUBCAUSE_NONE as the assertSubcause.  An application
 *              developer could trap any malloc failure on the stack by calling
 *              HAL_ASSERT_SPINLOCK under the matching case.
 *
 *              An application developer is encouraged to extend this function
 *              for use by their own application.  To do this, add assert.c
 *              to your project workspace, the path to assert.h (this can
 *              be found on the stack side). Asserts are raised by including
 *              assert.h and using macro HAL_ASSERT(cause) to raise an
 *              assert with argument assertCause.  the assertSubcause may be
 *              optionally set by macro HAL_ASSERT_SET_SUBCAUSE(subCause) prior
 *              to asserting the cause it describes. More information is
 *              available in assert.h.
 *
 * input parameters
 *
 * @param       assertCause    - Assert cause as defined in assert.h.
 * @param       assertSubcause - Optional assert subcause (see assert.h).
 *
 * output parameters
 *
 * @param       None.
 *
 * @return      None.
 */
void AssertHandler(uint8_t assertCause, uint8_t assertSubcause)
{
    // check the assert cause
    switch(assertCause)
    {
        case HAL_ASSERT_CAUSE_OUT_OF_MEMORY:
        {
            // ERROR: OUT OF MEMORY
            HAL_ASSERT_SPINLOCK;
            break;
        }

        case HAL_ASSERT_CAUSE_INTERNAL_ERROR:
        {
            // check the subcause
            if(assertSubcause == HAL_ASSERT_SUBCAUSE_FW_INERNAL_ERROR)
            {
                // ERROR: INTERNAL FW ERROR
                HAL_ASSERT_SPINLOCK;
            }
            else
            {
                // ERROR: INTERNAL ERROR
                HAL_ASSERT_SPINLOCK;
            }
            break;
        }

        case HAL_ASSERT_CAUSE_ICALL_ABORT:
        {
            HAL_ASSERT_SPINLOCK;
            break;
        }

        case HAL_ASSERT_CAUSE_ICALL_TIMEOUT:
        {
            HAL_ASSERT_SPINLOCK;
            break;
        }

        case HAL_ASSERT_CAUSE_WRONG_API_CALL:
        {
            HAL_ASSERT_SPINLOCK;
            break;
        }

        case HAL_ASSERT_CAUSE_STACK_OVERFLOW_ERROR:
        {
            HAL_ASSERT_SPINLOCK;
            break;
        }

        case HAL_ASSERT_CAUSE_LL_INIT_RNG_NOISE_FAILURE:
        {
            /*
             * Device must be reset to recover from this case.
             *
             * The HAL_ASSERT_SPINLOCK with is replacable with custom handling,
             * at the end of which Power_reset(); MUST be called.
             *
             * BLE5-stack functionality will be compromised when LL_initRNGNoise
             * fails.
             */
            HAL_ASSERT_SPINLOCK;
            break;
        }

        default:
        {
            HAL_ASSERT_SPINLOCK;
            break;
        }
    }

    return;
}

/*******************************************************************************
 */
