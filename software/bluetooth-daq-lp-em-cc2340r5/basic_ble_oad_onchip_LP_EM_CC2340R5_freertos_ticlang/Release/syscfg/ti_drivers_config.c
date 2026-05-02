/*
 *  ======== ti_drivers_config.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the LP_EM_CC2340R5
 *  by the SysConfig tool.
 */

#include <stddef.h>
#include <stdint.h>

#ifndef DeviceFamily_CC23X0R5
#define DeviceFamily_CC23X0R5
#endif

#include <ti/devices/DeviceFamily.h>

#include "ti_drivers_config.h"

/*
 *  =============================== ADC ===============================
 */

#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCLPF3.h>
#include <ti/drivers/GPIO.h>

#define CONFIG_ADC_COUNT 2

/*
 *  ======== ADCLPF3_objects ========
 */
ADCLPF3_Object ADCLPF3_objects[CONFIG_ADC_COUNT];

/*
 *  ======== ADCLPF3_hwAttrs ========
 */
const ADCLPF3_HWAttrs ADCLPF3_hwAttrs[CONFIG_ADC_COUNT] = {
    /* CONFIG_ADC_0 */
    {
        .adcInputDIO         = CONFIG_GPIO_ADC_0_CHANNEL,
        .adcRefPosDIO        = GPIO_INVALID_INDEX,
        .adcRefNegDIO        = GPIO_INVALID_INDEX,
        .internalChannel     = 0,
        .refSource           = ADCLPF3_VDDS_REFERENCE,
        .samplingDuration    = 32,
        .refVoltage          = 3300000,
        .returnAdjustedVal   = false,
        .resolutionBits      = ADCLPF3_RESOLUTION_12_BIT,
        .adcClkkDivider      = ADCLPF3_CLKDIV_8
    },
    /* CONFIG_ADC_1 */
    {
        .adcInputDIO         = CONFIG_GPIO_ADC_1_CHANNEL,
        .adcRefPosDIO        = GPIO_INVALID_INDEX,
        .adcRefNegDIO        = GPIO_INVALID_INDEX,
        .internalChannel     = 2,
        .refSource           = ADCLPF3_VDDS_REFERENCE,
        .samplingDuration    = 16,
        .refVoltage          = 3300000,
        .returnAdjustedVal   = false,
        .resolutionBits      = ADCLPF3_RESOLUTION_12_BIT,
        .adcClkkDivider      = ADCLPF3_CLKDIV_32
    },
};

/*
 *  ======== ADC_config ========
 */
const ADC_Config ADC_config[CONFIG_ADC_COUNT] = {
    /* CONFIG_ADC_0 */
    {
        .fxnTablePtr    = &ADCLPF3_fxnTable,
        .object         = &ADCLPF3_objects[CONFIG_ADC_0],
        .hwAttrs        = &ADCLPF3_hwAttrs[CONFIG_ADC_0]
    },
    /* CONFIG_ADC_1 */
    {
        .fxnTablePtr    = &ADCLPF3_fxnTable,
        .object         = &ADCLPF3_objects[CONFIG_ADC_1],
        .hwAttrs        = &ADCLPF3_hwAttrs[CONFIG_ADC_1]
    },
};

const uint_least8_t CONFIG_ADC_0_CONST = CONFIG_ADC_0;
const uint_least8_t CONFIG_ADC_1_CONST = CONFIG_ADC_1;
const uint_least8_t ADC_count = CONFIG_ADC_COUNT;

/*
 *  =============================== AESCCM ===============================
 */

#include <ti/drivers/AESCCM.h>
#include <ti/drivers/aesccm/AESCCMLPF3.h>

#define CONFIG_AESCCM_COUNT 1
AESCCMLPF3_Object AESCCMLPF3_objects[CONFIG_AESCCM_COUNT];

/*
 *  ======== AESCCMLPF3_hwAttrs ========
 */
const AESCCMLPF3_HWAttrs AESCCMLPF3_hwAttrs[CONFIG_AESCCM_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const AESCCM_Config AESCCM_config[CONFIG_AESCCM_COUNT] = {
    {   /* CONFIG_AESCCM0 */
        .object  = &AESCCMLPF3_objects[CONFIG_AESCCM0],
        .hwAttrs = &AESCCMLPF3_hwAttrs[CONFIG_AESCCM0]
    },
};

const uint_least8_t CONFIG_AESCCM0_CONST = CONFIG_AESCCM0;
const uint_least8_t AESCCM_count = CONFIG_AESCCM_COUNT;

/*
 *  =============================== AESCTRDRBG ===============================
 */

#include <ti/drivers/AESCTRDRBG.h>
#include <ti/drivers/aesctrdrbg/AESCTRDRBGXX.h>

#define CONFIG_AESCTRDRBG_COUNT 1

/*
 *  ======== aesctrdrbgXXObjects ========
 */
AESCTRDRBGXX_Object aesctrdrbgXXObjects[CONFIG_AESCTRDRBG_COUNT];

/*
 *  ======== aesctrdrbgXXHWAttrs ========
 */
const AESCTRDRBGXX_HWAttrs aesctrdrbgXXHWAttrs[CONFIG_AESCTRDRBG_COUNT] = {
    /* CONFIG_AESCTRDRBG_0 */
    {
        .aesctrHWAttrs.intPriority = (~0)
    },
};

/*
 *  ======== AESCTRDRBG_config ========
 */
const AESCTRDRBG_Config AESCTRDRBG_config[CONFIG_AESCTRDRBG_COUNT] = {
    /* CONFIG_AESCTRDRBG_0 */
    {
        .object = &aesctrdrbgXXObjects[CONFIG_AESCTRDRBG_0],
        .hwAttrs = &aesctrdrbgXXHWAttrs[CONFIG_AESCTRDRBG_0]
    },
};

const uint_least8_t CONFIG_AESCTRDRBG_0_CONST = CONFIG_AESCTRDRBG_0;
const uint_least8_t AESCTRDRBG_count = CONFIG_AESCTRDRBG_COUNT;

/*
 *  =============================== AESECB ===============================
 */

#include <ti/drivers/AESECB.h>
#include <ti/drivers/aesecb/AESECBLPF3.h>

#define CONFIG_AESECB_COUNT 1
AESECBLPF3_Object AESECBLPF3_objects[CONFIG_AESECB_COUNT];

/*
 *  ======== AESECBLPF3_hwAttrs ========
 */
const AESECBLPF3_HWAttrs AESECBLPF3_hwAttrs[CONFIG_AESECB_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const AESECB_Config AESECB_config[CONFIG_AESECB_COUNT] = {
    {   /* CONFIG_AESECB0 */
        .object  = &AESECBLPF3_objects[CONFIG_AESECB0],
        .hwAttrs = &AESECBLPF3_hwAttrs[CONFIG_AESECB0]
    },
};


const uint_least8_t CONFIG_AESECB0_CONST = CONFIG_AESECB0;
const uint_least8_t AESECB_count = CONFIG_AESECB_COUNT;

/*
 *  =============================== DMA ===============================
 */

#include <ti/drivers/dma/UDMALPF3.h>
#include <ti/devices/cc23x0r5/inc/hw_memmap.h>

const UDMALPF3_Config UDMALPF3_config = {
        .CtrlBaseAddr = UDMALPF3_CONFIG_BASE,
};

/*
 *  =============================== ECDH ===============================
 */

#include <ti/drivers/ECDH.h>
#include <ti/drivers/ecdh/ECDHLPF3SW.h>

#define CONFIG_ECDH_COUNT 1

ECDHLPF3SW_Object ecdhLpf3swObjects[CONFIG_ECDH_COUNT];

/*
 *  ======== ecdhLpf3swHWAttrs ========
 */
const ECDHLPF3SW_HWAttrs ecdhLpf3swHWAttrs[CONFIG_ECDH_COUNT] = {
    {0},
};

const ECDH_Config ECDH_config[CONFIG_ECDH_COUNT] = {
    {   /* CONFIG_ECDH0 */
        .object         = &ecdhLpf3swObjects[CONFIG_ECDH0],
        .hwAttrs        = &ecdhLpf3swHWAttrs[CONFIG_ECDH0]
    },
};

const uint_least8_t CONFIG_ECDH0_CONST = CONFIG_ECDH0;
const uint_least8_t ECDH_count = CONFIG_ECDH_COUNT;

/*
 *  =============================== GPIO ===============================
 */

#include <ti/drivers/GPIO.h>

/* The range of pins available on this device */
const uint_least8_t GPIO_pinLowerBound = 0;
const uint_least8_t GPIO_pinUpperBound = 25;

/*
 *  ======== gpioPinConfigs ========
 *  Array of Pin configurations
 */
GPIO_PinConfig gpioPinConfigs[26] = {
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_HIGH, /* CONFIG_DIN_LOAD */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_HIGH, /* CONFIG_DOUT_LOAD */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_HIGH, /* CONFIG_XSPI_SEL */
    GPIO_CFG_NO_DIR, /* DIO_3 */
    GPIO_CFG_NO_DIR, /* DIO_4 */
    /* Owned by CONFIG_ADC_1_CHANNEL as ADC_1_CHANNEL */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_NONE_INTERNAL, /* CONFIG_GPIO_ADC_1_CHANNEL */
    /* Owned by CONFIG_UART as TX */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_HIGH, /* CONFIG_GPIO_UART_TX */
    /* Owned by CONFIG_ADC_0_CHANNEL as ADC_0_CHANNEL */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_NONE_INTERNAL, /* CONFIG_GPIO_ADC_0_CHANNEL */
    /* Owned by CONFIG_I2C_0 as SDA */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_UP_INTERNAL, /* CONFIG_GPIO_I2C_0_SDA */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_DACEN */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* CONFIG_MUX2 */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_HIGH, /* CONFIG_ADCCS */
    /* Owned by CONFIG_SPI as POCI */
    GPIO_CFG_DO_NOT_CONFIG, /* CONFIG_GPIO_SPI_POCI */
    /* Owned by CONFIG_SPI as PICO */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_HIGH, /* CONFIG_GPIO_SPI_PICO */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_HIGH, /* CONFIG_SDADCDIS */
    /* Owned by CONFIG_UART as RX */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_DOWN_INTERNAL, /* CONFIG_GPIO_UART_RX */
    GPIO_CFG_DO_NOT_CONFIG, /* DIO_16 */
    GPIO_CFG_DO_NOT_CONFIG, /* DIO_17 */
    /* Owned by CONFIG_SPI as SCLK */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_GPIO_SPI_SCLK */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_UART_SEL */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_MUX1 */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_XRAM_SEL */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_MUX0 */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_XCVR_DRV_EN */
    /* Owned by CONFIG_I2C_0 as SCL */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_UP_INTERNAL, /* CONFIG_GPIO_I2C_0_SCL */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_I2C_SEL */
};

/*
 *  ======== gpioCallbackFunctions ========
 *  Array of callback function pointers
 *  Change at runtime with GPIO_setCallback()
 */
GPIO_CallbackFxn gpioCallbackFunctions[26];

/*
 *  ======== gpioUserArgs ========
 *  Array of user argument pointers
 *  Change at runtime with GPIO_setUserArg()
 *  Get values with GPIO_getUserArg()
 */
void* gpioUserArgs[26];

const uint_least8_t CONFIG_GPIO_ADC_0_CHANNEL_CONST = CONFIG_GPIO_ADC_0_CHANNEL;
const uint_least8_t CONFIG_GPIO_ADC_1_CHANNEL_CONST = CONFIG_GPIO_ADC_1_CHANNEL;
const uint_least8_t CONFIG_UART_SEL_CONST = CONFIG_UART_SEL;
const uint_least8_t CONFIG_XRAM_SEL_CONST = CONFIG_XRAM_SEL;
const uint_least8_t CONFIG_DIN_LOAD_CONST = CONFIG_DIN_LOAD;
const uint_least8_t CONFIG_DOUT_LOAD_CONST = CONFIG_DOUT_LOAD;
const uint_least8_t CONFIG_XCVR_DRV_EN_CONST = CONFIG_XCVR_DRV_EN;
const uint_least8_t CONFIG_I2C_SEL_CONST = CONFIG_I2C_SEL;
const uint_least8_t CONFIG_XSPI_SEL_CONST = CONFIG_XSPI_SEL;
const uint_least8_t CONFIG_MUX0_CONST = CONFIG_MUX0;
const uint_least8_t CONFIG_MUX1_CONST = CONFIG_MUX1;
const uint_least8_t CONFIG_MUX2_CONST = CONFIG_MUX2;
const uint_least8_t CONFIG_DACEN_CONST = CONFIG_DACEN;
const uint_least8_t CONFIG_SDADCDIS_CONST = CONFIG_SDADCDIS;
const uint_least8_t CONFIG_ADCCS_CONST = CONFIG_ADCCS;
const uint_least8_t CONFIG_GPIO_I2C_0_SDA_CONST = CONFIG_GPIO_I2C_0_SDA;
const uint_least8_t CONFIG_GPIO_I2C_0_SCL_CONST = CONFIG_GPIO_I2C_0_SCL;
const uint_least8_t CONFIG_GPIO_SPI_SCLK_CONST = CONFIG_GPIO_SPI_SCLK;
const uint_least8_t CONFIG_GPIO_SPI_POCI_CONST = CONFIG_GPIO_SPI_POCI;
const uint_least8_t CONFIG_GPIO_SPI_PICO_CONST = CONFIG_GPIO_SPI_PICO;
const uint_least8_t CONFIG_GPIO_UART_TX_CONST = CONFIG_GPIO_UART_TX;
const uint_least8_t CONFIG_GPIO_UART_RX_CONST = CONFIG_GPIO_UART_RX;

/*
 *  ======== GPIO_config ========
 */
const GPIO_Config GPIO_config = {
    .configs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .userArgs = gpioUserArgs,
    .intPriority = (~0)
};

/*
 *  =============================== I2C ===============================
 */

#include <ti/drivers/I2C.h>
#include <ti/drivers/i2c/I2CLPF3.h>
#include <ti/drivers/Power.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)

#define CONFIG_I2C_COUNT 1

/*
 *  ======== I2CLPF3_objects ========
 */
I2CLPF3_Object I2CLPF3_objects[CONFIG_I2C_COUNT];

/*
 *  ======== I2CLPF3_hwAttrs ========
 */
const I2CLPF3_HWAttrs I2CLPF3_hwAttrs[CONFIG_I2C_COUNT] = {
    /* CONFIG_I2C_0 */
    {
        .baseAddr    = I2C0_BASE,
        .powerMngrId = PowerLPF3_PERIPH_I2C0,
        .intNum      = INT_I2C0_IRQ,
        .intPriority = (~0),
        .swiPriority = 0,
        .sclPin      = CONFIG_GPIO_I2C_0_SCL,
        .sclPinMux   = GPIO_MUX_PORTCFG_PFUNC5,
        .sdaPin      = CONFIG_GPIO_I2C_0_SDA,
        .sdaPinMux   = GPIO_MUX_PORTCFG_PFUNC4
    },
};

/*
 *  ======== I2C_config ========
 */
const I2C_Config I2C_config[CONFIG_I2C_COUNT] = {
    /* CONFIG_I2C_0 */
    {
        .object      = &I2CLPF3_objects[CONFIG_I2C_0],
        .hwAttrs     = &I2CLPF3_hwAttrs[CONFIG_I2C_0]
    },
};

const uint_least8_t CONFIG_I2C_0_CONST = CONFIG_I2C_0;
const uint_least8_t I2C_count = CONFIG_I2C_COUNT;

/*
 *  =============== LGPTimer ===============
 */

#include <ti/drivers/timer/LGPTimerLPF3.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/GPIO.h>
#include <ti/devices/cc23x0r5/inc/hw_memmap.h>
#include <ti/devices/cc23x0r5/inc/hw_ints.h>

#define CONFIG_LGPTIMER_COUNT 2

/*
 *  ======== LGPTimerLPF3_objects ========
 */
LGPTimerLPF3_Object LGPTimerLPF3_objects[CONFIG_LGPTIMER_COUNT];

/*
 *  ======== LGPTimerLPF3_hwAttrs ========
 */
static const LGPTimerLPF3_HWAttrs LGPTimerLPF3_hwAttrs[CONFIG_LGPTIMER_COUNT] = {
  {
    .baseAddr           = LGPT1_BASE,
    .intNum             = INT_LGPT1_COMB,
    .intPriority        = 0x80,
    .powerID            = PowerLPF3_PERIPH_LGPT1,
    .channelConfig[0]   = {
        .pin     = GPIO_INVALID_INDEX,
        .pinMux  = GPIO_MUX_GPIO_INTERNAL,
        .nPin    = GPIO_INVALID_INDEX,
        .nPinMux = GPIO_MUX_GPIO_INTERNAL,
    },
    .channelConfig[1]   = {
        .pin     = GPIO_INVALID_INDEX,
        .pinMux  = GPIO_MUX_GPIO_INTERNAL,
        .nPin    = GPIO_INVALID_INDEX,
        .nPinMux = GPIO_MUX_GPIO_INTERNAL,
    },
    .channelConfig[2]   = {
        .pin     = GPIO_INVALID_INDEX,
        .pinMux  = GPIO_MUX_GPIO_INTERNAL,
        .nPin    = GPIO_INVALID_INDEX,
        .nPinMux = GPIO_MUX_GPIO_INTERNAL,
    },
  },
  {
    .baseAddr           = LGPT0_BASE,
    .intNum             = INT_LGPT0_COMB,
    .intPriority        = 0x40,
    .powerID            = PowerLPF3_PERIPH_LGPT0,
    .channelConfig[0]   = {
        .pin     = GPIO_INVALID_INDEX,
        .pinMux  = GPIO_MUX_GPIO_INTERNAL,
        .nPin    = GPIO_INVALID_INDEX,
        .nPinMux = GPIO_MUX_GPIO_INTERNAL,
    },
    .channelConfig[1]   = {
        .pin     = GPIO_INVALID_INDEX,
        .pinMux  = GPIO_MUX_GPIO_INTERNAL,
        .nPin    = GPIO_INVALID_INDEX,
        .nPinMux = GPIO_MUX_GPIO_INTERNAL,
    },
    .channelConfig[2]   = {
        .pin     = GPIO_INVALID_INDEX,
        .pinMux  = GPIO_MUX_GPIO_INTERNAL,
        .nPin    = GPIO_INVALID_INDEX,
        .nPinMux = GPIO_MUX_GPIO_INTERNAL,
    },
  },
};

/*
 *  ======== LGPTimer_config ========
 */
const LGPTimerLPF3_Config LGPTimerLPF3_config[CONFIG_LGPTIMER_COUNT] = {
    {   /* CONFIG_LGPTIMER_0 */
        .object      = &LGPTimerLPF3_objects[CONFIG_LGPTIMER_0],
        .hwAttrs     = &LGPTimerLPF3_hwAttrs[CONFIG_LGPTIMER_0]
    },
    {   /* CONFIG_LGPTIMER_1 */
        .object      = &LGPTimerLPF3_objects[CONFIG_LGPTIMER_1],
        .hwAttrs     = &LGPTimerLPF3_hwAttrs[CONFIG_LGPTIMER_1]
    },
};

const uint_least8_t CONFIG_LGPTIMER_0_CONST = CONFIG_LGPTIMER_0;
const uint_least8_t CONFIG_LGPTIMER_1_CONST = CONFIG_LGPTIMER_1;
const uint_least8_t LGPTimerLPF3_count = CONFIG_LGPTIMER_COUNT;

/*
 *  =============================== NVS ===============================
 */

#include <ti/drivers/NVS.h>
#include <ti/drivers/nvs/NVSLPF3.h>

/*
 *  NVSLPF3 Internal NVS flash region definitions
 *
 * Place uninitialized char arrays at addresses
 * corresponding to the 'regionBase' addresses defined in
 * the configured NVS regions. These arrays are used as
 * place holders so that the linker will not place other
 * content there.
 *
 * For GCC targets, the char arrays are each placed into
 * the shared ".nvs" section. The user must add content to
 * their GCC linker command file to place the .nvs section
 * at the lowest 'regionBase' address specified in their NVS
 * regions.
 */

#if defined(__TI_COMPILER_VERSION__) || defined(__clang__)

static char flashBuf0[0x3000] __attribute__ ((retain, noinit, location(0x7d000)));

#elif defined(__IAR_SYSTEMS_ICC__)

__no_init static char flashBuf0[0x3000] @ 0x7d000;

#elif defined(__GNUC__)

__attribute__ ((section (".nvs")))
static char flashBuf0[0x3000];

#endif

NVSLPF3_Object NVSLPF3_objects[2];

static const NVSLPF3_HWAttrs NVSLPF3_hwAttrs[2] = {
    /* CONFIG_NVSINTERNAL */
    {
        .regionBase = (void *) flashBuf0,
        .regionSize = 0x3000
    },
    /* CONFIG_NVSINTERNAL1 */
    {
        .regionBase = (void *) 0x32000,
        .regionSize = 0x4a000
    },
};

#define CONFIG_NVS_COUNT 2

const NVS_Config NVS_config[CONFIG_NVS_COUNT] = {
    /* CONFIG_NVSINTERNAL */
    {
        .fxnTablePtr = &NVSLPF3_fxnTable,
        .object = &NVSLPF3_objects[0],
        .hwAttrs = &NVSLPF3_hwAttrs[0],
    },
    /* CONFIG_NVSINTERNAL1 */
    {
        .fxnTablePtr = &NVSLPF3_fxnTable,
        .object = &NVSLPF3_objects[1],
        .hwAttrs = &NVSLPF3_hwAttrs[1],
    },
};

const uint_least8_t CONFIG_NVSINTERNAL_CONST = CONFIG_NVSINTERNAL;
const uint_least8_t CONFIG_NVSINTERNAL1_CONST = CONFIG_NVSINTERNAL1;
const uint_least8_t NVS_count = CONFIG_NVS_COUNT;

/*
 *  =============================== Power ===============================
 */
#include <ti/drivers/Power.h>
#include "ti_drivers_config.h"
#include DeviceFamily_constructPath(driverlib/ckmd.h)
#include DeviceFamily_constructPath(driverlib/pmctl.h)

extern void PowerCC23X0_standbyPolicy(void);

const uint32_t PowerLPF3_capArrayP0 = 553648128; /* floor(8.25 * 2^26) */
const uint32_t PowerLPF3_capArrayP1 = 4697620; /* floor(0.07 * 2^26) */
const uint8_t  PowerLPF3_capArrayShift = 26;  /* shift-value to bring floating-point coefficients to fixed-point */


const PowerCC23X0_Config PowerCC23X0_config = {
    .policyInitFxn              = NULL,
    .policyFxn                  = PowerCC23X0_standbyPolicy,
    .startInitialHfxtAmpCompFxn = NULL,
};





/*
 *  =============================== RNG ===============================
 */

#include <ti/drivers/RNG.h>
#include <ti/drivers/rng/RNGLPF3RF.h>

#define CONFIG_RNG_COUNT 1

const bool RNGLPF3RF_rctEnabled = true;
const int RNGLPF3RF_rctThreshold = 24 / 3;

const bool RNGLPF3RF_aptEnabled = true;
const int RNGLPF3RF_aptThreshold = 461;
const int RNGLPF3RF_aptBimodalThreshold = 369;

const size_t RNG_poolByteSize = RNG_POOL_BYTE_SIZE;
#if defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=4
#else
__attribute__((aligned(4)))
#endif
uint8_t  RNG_instancePool[RNG_POOL_BYTE_SIZE];

const RNG_ReturnBehavior RNGLPF3RF_returnBehavior = RNG_RETURN_BEHAVIOR_BLOCKING;

const RNGLPF3RF_HWAttrs RNGLPF3RF_hwAttrs = {
    .intPriority = (~0)
};

RNGLPF3RF_Object RNGLPF3RF_objects[CONFIG_RNG_COUNT];

const RNG_Config RNG_config[CONFIG_RNG_COUNT] = {
    {   /* CONFIG_RNG_0 */
        .object         = &RNGLPF3RF_objects[CONFIG_RNG_0],
        .hwAttrs        = &RNGLPF3RF_hwAttrs
    },
};

const uint_least8_t CONFIG_RNG_0_CONST = CONFIG_RNG_0;
const uint_least8_t RNG_count = CONFIG_RNG_COUNT;

const uint32_t RNGLPF3RF_noiseInputWordLen = 152;

uint32_t RNGLPF3RF_noiseConditioningKeyWord0 = 0x111de874;
uint32_t RNGLPF3RF_noiseConditioningKeyWord1 = 0x6cecb00e;
uint32_t RNGLPF3RF_noiseConditioningKeyWord2 = 0x7fb76dc5;
uint32_t RNGLPF3RF_noiseConditioningKeyWord3 = 0x8e020ca2;

/*
 *  =============================== SPI DMA ===============================
 */
#include <ti/drivers/SPI.h>
#include <ti/drivers/spi/SPILPF3DMA.h>
#include <ti/drivers/dma/UDMALPF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/evtsvt.h)

#define CONFIG_SPI_COUNT 1

/*
 *  ======== SPILPF3DMA_objects ========
 */
SPILPF3DMA_Object SPILPF3DMA_objects[CONFIG_SPI_COUNT];

/*
 * ======== SPILPF3DMA uDMA Table Entries  ========
 */
ALLOCATE_CONTROL_TABLE_ENTRY(dmaChannel0ControlTableEntry, (0 | UDMA_PRI_SELECT));
ALLOCATE_CONTROL_TABLE_ENTRY(dmaChannel1ControlTableEntry, (1 | UDMA_PRI_SELECT));
ALLOCATE_CONTROL_TABLE_ENTRY(dmaChannel0AltControlTableEntry, (0 | UDMA_ALT_SELECT));
ALLOCATE_CONTROL_TABLE_ENTRY(dmaChannel1AltControlTableEntry, (1 | UDMA_ALT_SELECT));

/*
 *  ======== SPILPF3DMA_hwAttrs ========
 */
const SPILPF3DMA_HWAttrs SPILPF3DMA_hwAttrs[CONFIG_SPI_COUNT] = {


    {
        .baseAddr              = SPI0_BASE,
        .intNum                = INT_SPI0_COMB,
        .intPriority           = (~0),
        .swiPriority           = 0,
        .defaultTxBufValue     = 0xFF,
        .rxChannelBitMask      = UDMA_CHANNEL_1_M,
        .txChannelBitMask      = UDMA_CHANNEL_0_M,
        .rxChannelEvtMux       = EVTSVT_DMA_TRIG_SPI0RXTRG,
        .txChannelEvtMux       = EVTSVT_DMA_TRIG_SPI0TXTRG,
        .rxChannelSubscriberId = EVTSVT_DMA_CH1,
        .txChannelSubscriberId = EVTSVT_DMA_CH0,
        .dmaTxTableEntryPri    = &dmaChannel0ControlTableEntry,
        .dmaRxTableEntryPri    = &dmaChannel1ControlTableEntry,
        .dmaTxTableEntryAlt    = &dmaChannel0AltControlTableEntry,
        .dmaRxTableEntryAlt    = &dmaChannel1AltControlTableEntry,
        .minDmaTransferSize    = 2,
        .picoPinMux            = GPIO_MUX_PORTCFG_PFUNC2,
        .pociPinMux            = GPIO_MUX_PORTCFG_PFUNC1,
        .sclkPinMux            = GPIO_MUX_PORTCFG_PFUNC4,
        .picoPin               = CONFIG_GPIO_SPI_PICO,
        .pociPin               = CONFIG_GPIO_SPI_POCI,
        .sclkPin               = CONFIG_GPIO_SPI_SCLK,
        .csnPin                = GPIO_INVALID_INDEX,
        .powerID               = PowerLPF3_PERIPH_SPI0,
    },
};

/*
 *  ======== SPI_config ========
 */
const SPI_Config SPI_config[CONFIG_SPI_COUNT] = {
    /* CONFIG_SPI */
    /* LaunchPad SPI Bus */
    {
        .fxnTablePtr = &SPILPF3DMA_fxnTable,
        .object = &SPILPF3DMA_objects[CONFIG_SPI],
        .hwAttrs = &SPILPF3DMA_hwAttrs[CONFIG_SPI]
    },
};

const uint_least8_t CONFIG_SPI_CONST = CONFIG_SPI;
const uint_least8_t SPI_count = CONFIG_SPI_COUNT;

/*
 *  =============================== UART2 ===============================
 */

#include <ti/drivers/UART2.h>
#include <ti/drivers/uart2/UART2LPF3.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/dma/UDMALPF3.h>
#include <ti/drivers/Power.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(driverlib/evtsvt.h)

#define CONFIG_UART2_COUNT 1

UART2LPF3_Object UART2LPF3_objects[CONFIG_UART2_COUNT];

static unsigned char uart2RxRingBuffer0[32];
/* TX ring buffer allocated to be used for nonblocking mode */
static unsigned char uart2TxRingBuffer0[32];



ALLOCATE_CONTROL_TABLE_ENTRY(dmaChannel3ControlTableEntry, 3);
ALLOCATE_CONTROL_TABLE_ENTRY(dmaChannel2ControlTableEntry, 2);

static const UART2LPF3_HWAttrs UART2LPF3_hwAttrs[CONFIG_UART2_COUNT] = {
  {
    .baseAddr              = UART0_BASE,
    .intNum                = INT_UART0_COMB,
    .intPriority           = (~0),
    .rxPin                 = CONFIG_GPIO_UART_RX,
    .txPin                 = CONFIG_GPIO_UART_TX,
    .ctsPin                = GPIO_INVALID_INDEX,
    .rtsPin                = GPIO_INVALID_INDEX,
    .flowControl           = UART2_FLOWCTRL_NONE,
    .rxBufPtr              = uart2RxRingBuffer0,
    .rxBufSize             = sizeof(uart2RxRingBuffer0),
    .txBufPtr              = uart2TxRingBuffer0,
    .txBufSize             = sizeof(uart2TxRingBuffer0),
    .txPinMux              = GPIO_MUX_PORTCFG_PFUNC5,
    .rxPinMux              = GPIO_MUX_PORTCFG_PFUNC1,
    .ctsPinMux             = GPIO_MUX_GPIO_INTERNAL,
    .rtsPinMux             = GPIO_MUX_GPIO_INTERNAL,
    .dmaRxTableEntryPri    = &dmaChannel3ControlTableEntry,
    .dmaTxTableEntryPri    = &dmaChannel2ControlTableEntry,
    .rxChannelMask         = UDMA_CHANNEL_3_M,
    .txChannelMask         = UDMA_CHANNEL_2_M,
    .rxChannelEvtMux       = EVTSVT_DMA_TRIG_UART0RXTRG,
    .txChannelEvtMux       = EVTSVT_DMA_TRIG_UART0TXTRG,
    .txChannelSubscriberId = EVTSVT_DMA_CH2,
    .rxChannelSubscriberId = EVTSVT_DMA_CH3,
    .codingScheme          = UART2LPF3_CODING_UART,
    .concatenateFIFO       = false,
    .irLPClkDivider        = 8,
    .powerID               = PowerLPF3_PERIPH_UART0
  },
};

const UART2_Config UART2_config[CONFIG_UART2_COUNT] = {
    {   /* CONFIG_UART */
        .object      = &UART2LPF3_objects[CONFIG_UART],
        .hwAttrs     = &UART2LPF3_hwAttrs[CONFIG_UART]
    },
};

const uint_least8_t CONFIG_UART_CONST = CONFIG_UART;
const uint_least8_t UART2_count = CONFIG_UART2_COUNT;


/*
 *  =============================== BatMon Support ===============================
 */
#include <ti/drivers/batterymonitor/BatMonSupportLPF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_ints.h)
#include DeviceFamily_constructPath(driverlib/evtsvt.h)

const BatMonSupportLPF3_Config BatMonSupportLPF3_config = {
    .intNum = INT_CPUIRQ2,
    .intPriority = (~0),
    .intSubscriberId = EVTSVT_SUB_CPUIRQ2,
};

#include <stdbool.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/cpu.h)

#include <ti/drivers/GPIO.h>

/* Board GPIO defines */
#define BOARD_EXT_FLASH_SPI_CS      6
#define BOARD_EXT_FLASH_SPI_CLK     18
#define BOARD_EXT_FLASH_SPI_PICO    13
#define BOARD_EXT_FLASH_SPI_POCI    12

/*
 *  ======== Board_sendExtFlashByte ========
 */
void Board_sendExtFlashByte(uint8_t byte)
{
    uint8_t i;

    /* SPI Flash CS */
    GPIO_write(BOARD_EXT_FLASH_SPI_CS, 0);

    for (i = 0; i < 8; i++) {
        GPIO_write(BOARD_EXT_FLASH_SPI_CLK, 0); /* SPI Flash CLK */

        /* SPI Flash PICO */
        GPIO_write(BOARD_EXT_FLASH_SPI_PICO, (byte >> (7 - i)) & 0x01);
        GPIO_write(BOARD_EXT_FLASH_SPI_CLK, 1);  /* SPI Flash CLK */

        /*
         * Waste a few cycles to keep the CLK high for at
         * least 45% of the period.
         * 3 cycles per loop: 8 loops @ 48 MHz = 0.5 us.
         */
        CPUDelay(8);
    }

    GPIO_write(BOARD_EXT_FLASH_SPI_CLK, 0);  /* CLK */
    GPIO_write(BOARD_EXT_FLASH_SPI_CS, 1);  /* CS */

    /*
     * Keep CS high at least 40 us
     * 3 cycles per loop: 700 loops @ 48 MHz ~= 44 us
     */
    CPUDelay(700);
}

/*
 *  ======== Board_wakeUpExtFlash ========
 */
void Board_wakeUpExtFlash(void)
{
    /* SPI Flash CS*/
    GPIO_setConfig(BOARD_EXT_FLASH_SPI_CS, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_HIGH | GPIO_CFG_OUT_STR_MED);

    /*
     *  To wake up we need to toggle the chip select at
     *  least 20 ns and ten wait at least 35 us.
     */

    /* Toggle chip select for ~20ns to wake ext. flash */
    GPIO_write(BOARD_EXT_FLASH_SPI_CS, 0);
    /* 3 cycles per loop: 1 loop @ 48 MHz ~= 62 ns */
    CPUDelay(1);
    GPIO_write(BOARD_EXT_FLASH_SPI_CS, 1);
    /* 3 cycles per loop: 560 loops @ 48 MHz ~= 35 us */
    CPUDelay(560);
}

/*
 *  ======== Board_shutDownExtFlash ========
 */
void Board_shutDownExtFlash(void)
{
    /*
     *  To be sure we are putting the flash into sleep and not waking it,
     *  we first have to make a wake up call
     */
    Board_wakeUpExtFlash();

    /* SPI Flash CS*/
    GPIO_setConfig(BOARD_EXT_FLASH_SPI_CS, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_HIGH | GPIO_CFG_OUT_STR_MED);
    /* SPI Flash CLK */
    GPIO_setConfig(BOARD_EXT_FLASH_SPI_CLK, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_LOW | GPIO_CFG_OUT_STR_MED);
    /* SPI Flash PICO */
    GPIO_setConfig(BOARD_EXT_FLASH_SPI_PICO, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_LOW | GPIO_CFG_OUT_STR_MED);
    /* SPI Flash POCI */
    GPIO_setConfig(BOARD_EXT_FLASH_SPI_POCI, GPIO_CFG_IN_PD);

    uint8_t extFlashShutdown = 0xB9;

    Board_sendExtFlashByte(extFlashShutdown);

    GPIO_resetConfig(BOARD_EXT_FLASH_SPI_CS);
    GPIO_resetConfig(BOARD_EXT_FLASH_SPI_CLK);
    GPIO_resetConfig(BOARD_EXT_FLASH_SPI_PICO);
    GPIO_resetConfig(BOARD_EXT_FLASH_SPI_POCI);
}


#include <ti/drivers/Board.h>

/*
 *  ======== Board_initHook ========
 *  Perform any board-specific initialization needed at startup.  This
 *  function is declared weak to allow applications to override it if needed.
 */
void __attribute__((weak)) Board_initHook(void)
{
}

/*
 *  ======== Board_init ========
 *  Perform any initialization needed before using any board APIs
 */
void Board_init(void)
{
    /* ==== /ti/drivers/Power initialization ==== */

    Power_init();
    PowerLPF3_selectLFXT();
    PMCTLSetVoltageRegulator(PMCTL_VOLTAGE_REGULATOR_DCDC);



    /* ==== /ti/drivers/GPIO initialization ==== */
    /* Setup GPIO module and default-initialise pins */
    GPIO_init();

    /* ==== /ti/drivers/DMA initialization ==== */
    UDMALPF3_init();

    /* ==== /ti/drivers/RCL initialization ==== */

    Board_shutDownExtFlash();

    Board_initHook();
}

