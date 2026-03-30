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
 *  =============================== DMA ===============================
 */

#include <ti/drivers/dma/UDMALPF3.h>
#include <ti/devices/cc23x0r5/inc/hw_memmap.h>

const UDMALPF3_Config UDMALPF3_config = {
        .CtrlBaseAddr = UDMALPF3_CONFIG_BASE,
};

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
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_MUX2 */
    /* Owned by CONFIG_UART as TX */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_HIGH, /* CONFIG_GPIO_UART_TX */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_DACEN */
    /* Owned by CONFIG_I2C_0 as SDA */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_UP_INTERNAL, /* CONFIG_GPIO_I2C_0_SDA */
    GPIO_CFG_NO_DIR, /* DIO_9 */
    GPIO_CFG_NO_DIR, /* DIO_10 */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_HIGH, /* CONFIG_ADCCS */
    /* Owned by CONFIG_SPI as POCI */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_NONE_INTERNAL, /* CONFIG_GPIO_SPI_POCI */
    /* Owned by CONFIG_SPI as PICO */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* CONFIG_GPIO_SPI_PICO */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_SDADCDIS */
    /* Owned by CONFIG_UART as RX */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_NONE_INTERNAL, /* CONFIG_GPIO_UART_RX */
    GPIO_CFG_DO_NOT_CONFIG, /* DIO_16 */
    GPIO_CFG_DO_NOT_CONFIG, /* DIO_17 */
    /* Owned by CONFIG_SPI as SCLK */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* CONFIG_GPIO_SPI_SCLK */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* CONFIG_UART_SEL */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_MUX1 */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_HIGH, /* CONFIG_XRAM_SEL */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_MUX0 */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* CONFIG_XCVR_DRV_EN */
    /* Owned by CONFIG_I2C_0 as SCL */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_UP_INTERNAL, /* CONFIG_GPIO_I2C_0_SCL */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* CONFIG_I2C_SEL */
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
        .defaultTxBufValue     = 0XFF,
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

static unsigned char uart2RxRingBuffer0[256];
/* TX ring buffer allocated to be used for nonblocking mode */
static unsigned char uart2TxRingBuffer0[256];



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

    Board_shutDownExtFlash();

    Board_initHook();
}

