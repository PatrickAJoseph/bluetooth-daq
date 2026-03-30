################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-4123678: ../bluetooth-daq.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.23.2/sysconfig_cli.bat" -s "C:/ti/simplelink_lowpower_f3_sdk_9_14_01_16/.metadata/product.json" --script "F:/Projects/bluetooth-daq/software/bluetooth-daq-lp-em-cc2340r5/bluetooth-daq/bluetooth-daq.syscfg" -o "syscfg" --compiler gcc
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_devices_config.c: build-4123678 ../bluetooth-daq.syscfg
syscfg/ti_drivers_config.c: build-4123678
syscfg/ti_drivers_config.h: build-4123678
syscfg/ti_utils_build_linker.cmd.genlibs: build-4123678
syscfg/ti_utils_build_linker.cmd.genmap: build-4123678
syscfg/ti_utils_build_compiler.opt: build-4123678
syscfg/syscfg_c.rov.xs: build-4123678
syscfg/FreeRTOSConfig.h: build-4123678
syscfg/ti_freertos_config.c: build-4123678
syscfg/ti_freertos_portable_config.c: build-4123678
syscfg: build-4123678

syscfg/%.o: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/gcc-arm-none-eabi_9_3_1/bin/arm-none-eabi-gcc-9.3.1.exe" -c -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft -D_REENT_SMALL -I"F:/Projects/bluetooth-daq/software/bluetooth-daq-lp-em-cc2340r5/bluetooth-daq" -I"F:/Projects/bluetooth-daq/software/bluetooth-daq-lp-em-cc2340r5/bluetooth-daq/Debug" -I"C:/ti/simplelink_lowpower_f3_sdk_9_14_01_16/source" -I"C:/ti/simplelink_lowpower_f3_sdk_9_14_01_16/kernel/freertos" -I"C:/ti/simplelink_lowpower_f3_sdk_9_14_01_16/source/ti/posix/gcc" -I"C:/ti/simplelink_lowpower_f3_sdk_9_14_01_16/source/third_party/freertos/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_14_01_16/source/third_party/freertos/portable/GCC/ARM_CM0" -I"C:/ti/gcc-arm-none-eabi_9_3_1/arm-none-eabi/include/newlib-nano" -I"F:/Projects/bluetooth-daq/software/bluetooth-daq-lp-em-cc2340r5/bluetooth-daq/sscp/src" -I"F:/Projects/bluetooth-daq/software/bluetooth-daq-lp-em-cc2340r5/bluetooth-daq/sscp/inc" -I"C:/ti/gcc-arm-none-eabi_9_3_1/arm-none-eabi/include" -Og -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"syscfg/$(basename $(<F)).d_raw" -MT"$(@)" -I"F:/Projects/bluetooth-daq/software/bluetooth-daq-lp-em-cc2340r5/bluetooth-daq/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/gcc-arm-none-eabi_9_3_1/bin/arm-none-eabi-gcc-9.3.1.exe" -c -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft -D_REENT_SMALL -I"F:/Projects/bluetooth-daq/software/bluetooth-daq-lp-em-cc2340r5/bluetooth-daq" -I"F:/Projects/bluetooth-daq/software/bluetooth-daq-lp-em-cc2340r5/bluetooth-daq/Debug" -I"C:/ti/simplelink_lowpower_f3_sdk_9_14_01_16/source" -I"C:/ti/simplelink_lowpower_f3_sdk_9_14_01_16/kernel/freertos" -I"C:/ti/simplelink_lowpower_f3_sdk_9_14_01_16/source/ti/posix/gcc" -I"C:/ti/simplelink_lowpower_f3_sdk_9_14_01_16/source/third_party/freertos/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_14_01_16/source/third_party/freertos/portable/GCC/ARM_CM0" -I"C:/ti/gcc-arm-none-eabi_9_3_1/arm-none-eabi/include/newlib-nano" -I"F:/Projects/bluetooth-daq/software/bluetooth-daq-lp-em-cc2340r5/bluetooth-daq/sscp/src" -I"F:/Projects/bluetooth-daq/software/bluetooth-daq-lp-em-cc2340r5/bluetooth-daq/sscp/inc" -I"C:/ti/gcc-arm-none-eabi_9_3_1/arm-none-eabi/include" -Og -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"F:/Projects/bluetooth-daq/software/bluetooth-daq-lp-em-cc2340r5/bluetooth-daq/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


