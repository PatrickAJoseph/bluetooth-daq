/*
 *  ======== ti_drivers_config.h ========
 *  Configured TI-Drivers module declarations
 *
 *  The macros defines herein are intended for use by applications which
 *  directly include this header. These macros should NOT be hard coded or
 *  copied into library source code.
 *
 *  Symbols declared as const are intended for use with libraries.
 *  Library source code must extern the correct symbol--which is resolved
 *  when the application is linked.
 *
 *  DO NOT EDIT - This file is generated for the LP_EM_CC2340R5
 *  by the SysConfig tool.
 */
#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#define CONFIG_SYSCONFIG_PREVIEW

#define CONFIG_LP_EM_CC2340R5
#ifndef DeviceFamily_CC23X0R5
#define DeviceFamily_CC23X0R5
#endif

#include <ti/devices/DeviceFamily.h>

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== ADC ========
 */

extern const uint_least8_t              CONFIG_ADC_0_CONST;
#define CONFIG_ADC_0                    0
extern const uint_least8_t              CONFIG_ADC_1_CONST;
#define CONFIG_ADC_1                    1
#define CONFIG_TI_DRIVERS_ADC_COUNT     2


/*
 *  ======== AESCCM ========
 */

extern const uint_least8_t                  CONFIG_AESCCM0_CONST;
#define CONFIG_AESCCM0                      0
#define CONFIG_TI_DRIVERS_AESCCM_COUNT      1


/*
 *  ======== AESCTRDRBG ========
 */

extern const uint_least8_t                      CONFIG_AESCTRDRBG_0_CONST;
#define CONFIG_AESCTRDRBG_0                     0
#define CONFIG_TI_DRIVERS_AESCTRDRBG_COUNT      1


/*
 *  ======== AESECB ========
 */

extern const uint_least8_t                  CONFIG_AESECB0_CONST;
#define CONFIG_AESECB0                      0
#define CONFIG_TI_DRIVERS_AESECB_COUNT      1


/*
 *  ======== ECDH ========
 */

extern const uint_least8_t              CONFIG_ECDH0_CONST;
#define CONFIG_ECDH0                    0
#define CONFIG_TI_DRIVERS_ECDH_COUNT    1


/*
 *  ======== GPIO ========
 */
/* Owned by CONFIG_ADC_0_CHANNEL as  */
extern const uint_least8_t CONFIG_GPIO_ADC_0_CHANNEL_CONST;
#define CONFIG_GPIO_ADC_0_CHANNEL 7

/* Owned by CONFIG_ADC_1_CHANNEL as  */
extern const uint_least8_t CONFIG_GPIO_ADC_1_CHANNEL_CONST;
#define CONFIG_GPIO_ADC_1_CHANNEL 5

extern const uint_least8_t CONFIG_UART_SEL_CONST;
#define CONFIG_UART_SEL 19

extern const uint_least8_t CONFIG_XRAM_SEL_CONST;
#define CONFIG_XRAM_SEL 21

extern const uint_least8_t CONFIG_DIN_LOAD_CONST;
#define CONFIG_DIN_LOAD 0

extern const uint_least8_t CONFIG_DOUT_LOAD_CONST;
#define CONFIG_DOUT_LOAD 1

extern const uint_least8_t CONFIG_XCVR_DRV_EN_CONST;
#define CONFIG_XCVR_DRV_EN 23

extern const uint_least8_t CONFIG_I2C_SEL_CONST;
#define CONFIG_I2C_SEL 25

extern const uint_least8_t CONFIG_XSPI_SEL_CONST;
#define CONFIG_XSPI_SEL 2

extern const uint_least8_t CONFIG_MUX0_CONST;
#define CONFIG_MUX0 22

extern const uint_least8_t CONFIG_MUX1_CONST;
#define CONFIG_MUX1 20

extern const uint_least8_t CONFIG_MUX2_CONST;
#define CONFIG_MUX2 10

extern const uint_least8_t CONFIG_DACEN_CONST;
#define CONFIG_DACEN 9

extern const uint_least8_t CONFIG_SDADCDIS_CONST;
#define CONFIG_SDADCDIS 14

extern const uint_least8_t CONFIG_ADCCS_CONST;
#define CONFIG_ADCCS 11

/* Owned by CONFIG_I2C_0 as  */
extern const uint_least8_t CONFIG_GPIO_I2C_0_SDA_CONST;
#define CONFIG_GPIO_I2C_0_SDA 8

/* Owned by CONFIG_I2C_0 as  */
extern const uint_least8_t CONFIG_GPIO_I2C_0_SCL_CONST;
#define CONFIG_GPIO_I2C_0_SCL 24

/* Owned by CONFIG_SPI as  */
extern const uint_least8_t CONFIG_GPIO_SPI_SCLK_CONST;
#define CONFIG_GPIO_SPI_SCLK 18

/* Owned by CONFIG_SPI as  */
extern const uint_least8_t CONFIG_GPIO_SPI_POCI_CONST;
#define CONFIG_GPIO_SPI_POCI 12

/* Owned by CONFIG_SPI as  */
extern const uint_least8_t CONFIG_GPIO_SPI_PICO_CONST;
#define CONFIG_GPIO_SPI_PICO 13

/* Owned by CONFIG_UART as  */
extern const uint_least8_t CONFIG_GPIO_UART_TX_CONST;
#define CONFIG_GPIO_UART_TX 6

/* Owned by CONFIG_UART as  */
extern const uint_least8_t CONFIG_GPIO_UART_RX_CONST;
#define CONFIG_GPIO_UART_RX 15

/* The range of pins available on this device */
extern const uint_least8_t GPIO_pinLowerBound;
extern const uint_least8_t GPIO_pinUpperBound;

/* LEDs are active high */
#define CONFIG_GPIO_LED_ON  (1)
#define CONFIG_GPIO_LED_OFF (0)

#define CONFIG_LED_ON  (CONFIG_GPIO_LED_ON)
#define CONFIG_LED_OFF (CONFIG_GPIO_LED_OFF)


/*
 *  ======== I2C ========
 */

/*
 *  SCL: DIO4_A7
 *  SDA: DIO
 */
extern const uint_least8_t              CONFIG_I2C_0_CONST;
#define CONFIG_I2C_0                    0
#define CONFIG_TI_DRIVERS_I2C_COUNT     1

/* ======== I2C Addresses and Speeds ======== */
#include <ti/drivers/I2C.h>

/* ---- CONFIG_I2C_0 I2C bus components ---- */

/* no components connected to CONFIG_I2C_0 */

/* CONFIG_I2C_0.maxBitRate configuration specified 400000 kbps */
#define CONFIG_I2C_0_MAXSPEED   (400000U) /* kbps */
#define CONFIG_I2C_0_MAXBITRATE ((I2C_BitRate)I2C_400kHz)


/*
 *  ======== LGPTimer ========
 */

/*
 *  CH2: Unassigned
 *  CH2N: Unassigned
 */
extern const uint_least8_t                  CONFIG_LGPTIMER_0_CONST;
#define CONFIG_LGPTIMER_0                   0
/*
 *  CH2: Unassigned
 *  CH2N: Unassigned
 */
extern const uint_least8_t                  CONFIG_LGPTIMER_1_CONST;
#define CONFIG_LGPTIMER_1                   1
#define CONFIG_TI_DRIVERS_LGPTIMER_COUNT    2


/*
 *  ======== NVS ========
 */

extern const uint_least8_t              CONFIG_NVSINTERNAL_CONST;
#define CONFIG_NVSINTERNAL              0
extern const uint_least8_t              CONFIG_NVSINTERNAL1_CONST;
#define CONFIG_NVSINTERNAL1             1
#define CONFIG_TI_DRIVERS_NVS_COUNT     2



/*
 *  ======== RCL ========
*/



/*
 *  ======== RNG ========
 */

extern const uint_least8_t              CONFIG_RNG_0_CONST;
#define CONFIG_RNG_0                    0
#define CONFIG_TI_DRIVERS_RNG_COUNT     1

#define RNG_POOL_BYTE_SIZE 32

#define RNG_NOISE_INPUT_WORD_SIZE 152


/*
 *  ======== SPI ========
 */

/*
 *  PICO: DIO13
 *  POCI: DIO12
 *  SCLK: DIO18
 *  LaunchPad SPI Bus
 */
extern const uint_least8_t              CONFIG_SPI_CONST;
#define CONFIG_SPI                      0
#define CONFIG_TI_DRIVERS_SPI_COUNT     1


/*
 *  ======== UART2 ========
 */

/*
 *  TX: DIO6A1_AR+
 *  RX: DIO15
 */
extern const uint_least8_t                  CONFIG_UART_CONST;
#define CONFIG_UART                         0
#define CONFIG_TI_DRIVERS_UART2_COUNT       1


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
