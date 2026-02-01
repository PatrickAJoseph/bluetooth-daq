# bluetooth-daq
A simple low-speed Bluetooth enabled DAQ consisting of HV/LV voltage, current measurement, LV analog I/O, resistance measurement, UART, I2C & SPI communication interfaces and a high speed ADC combining multiple functionalities within one device. The device can be operated through a mobile/PC application via Bluetooth or through RS-485 interface. 16 devices can be connected to the RS-485 interface.

## Goal of the product
1. Reduce the number of induvidual electronic test equipment required for electronic hardware/software development.

2. Combine commonly used electronic test functions within a single device

3. Enable versatile interface to the device (RS485, Bluetooth, Web) and test automation support to reduce effort of manual testing.

## Features of the product

### Hardware features

1. 16 low-speed logic level digital inputs (+/ 3.3V) (maximum sampling rate of 100 SPS)
2. 16 low-speed logic level digital outputs (0-3V) with maximum current limit of 5mA / channel (maximum sampling rate of 100 SPS).
3. 2 channel bi-polar differential high-resolution analog inputs (+/-, 50V, 6 digits) with maximum sampling rate of 2 kSPS/channel in single channel sampling mode.
4. 2 channel high speed bipolar differential analog acquisition channels (maximum input signal frequency of 10kHz)
5. 1 UART communication instance (UART_TX, UART_RX) with maximum baud rate of 115200.
6. 1 I2C communication instance (I2C_SDA, I2C_SCL) with maximum clock speed of 400 kHz.
7. 1 SPI communication instance (SPI_MOSI, SPI_MISO, SPI_nCS, SPI_SCLK) with maximum clock speed of 4 MHz.
8. 8 channel differental bi-polar low voltage analog inputs +/- 15V range.
9. 2 current measurement inputs (+/- 50V common mode voltage, and maximum current of 3A).
10. 2 resistance measurement inputs ( 1 ohm to 1 MOhm ).
11. 2 thermistor temperature measurement channels.
12. 8 low speed DC analog outputs.
13. RS-485 interface for remote control.

### Software features

1. RS-485 control of device through PC.
2. Bluetooth control of device from PC/Mobile application.
3. Firmware upgrade through Bluetooth using TI Simplelink Connect app.
4. Simple Web GUI interface for control of device.
5. Python scripting support for remote control of device from PC.
6. LabVIEW support for the device.

## Hardware block diagram

![alt text](<images/bluetooth-daq-design-Hardware Block Diagram.drawio (1).png>)

### High voltage analog inputs

The device provides 2 high voltage analog inputs with a range of +/- 50V and maximum input frequency of 200 Hz. The high voltage analog input front end attenuates the input voltage signal and adds bias to meet voltage level requirements of the sigma-delta ADC inputs.

### Current inputs

The device provides 2 current inputs with common mode voltage upto +/- 50V and a range of +/- 3A. The voltage drop across the
current measurement terminal is 0.1V/A.

### Low voltage analog inputs

The device provides 8 channel +/- 15V low voltage analog inputs.
Maximum input frequency per channel is set to 200 Hz.

### Resistance measurement

The device provides 2 channel resistance measurement feature.
The supported resistance measurement range is 1 ohm to 1 MOhm.

### High speed acquisition channels

The device provides 2 single ended high speed analog signal
acquisition channels with sampling frequency of 200 kSPS per
channel, limiting the combined input signal frequency to 10kHz.

### Thermistor temperature measurement channels

The device provides 2 thermistor temperature measurement channels.
The reference voltage for the thermistor interface is 2.5V and reference resistance is 10k. The device comes with a calibration table for a 10K NTC. If user uses any other NTC, then, the calibration table for thermistor has to be manually entered by the user via software.

### Sigma-Delta ADC

The heart of most of the analog to digital conversions is carried out by a 24-bit sigma-delta ADC (ADS131M02: https://www.ti.com/lit/ds/symlink/ads131m02.pdf?ts=1769953054375&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FADS131M02).

The input to each channel of the ADC is multiplexed with the help of analog multiplexer (CD4051: https://www.ti.com/lit/ds/symlink/cd4051b.pdf)

### Low speed analog outputs

The device provides 8 analog outputs with range +/- 10V. Since a sample and hold circuit is used at the output stage, the output current limit is 1mA and so an external buffer must be used. The DAC used in the solution is DAC101C081 (https://www.ti.com/product/DAC101C081)

### SPI SRAM

The device uses a 1 MBit SRAM to store samples acquired from various modules such as high speed ADC, digital inputs, digital output patterns etc. The SRAM used is 23LCV1024 (https://ww1.microchip.com/downloads/en/DeviceDoc/25156A.pdf)

### Digital inputs and outputs

The device provides 16 digital inputs and digital outputs. The digital inputs are read by the MCU through a 74HC165 shift register (https://www.ti.com/lit/ds/symlink/sn74hc165.pdf) and the digital outputs are transferred through 74HC595 shift register (https://www.ti.com/lit/ds/symlink/sn74hc595.pdf).

The digital inputs have a range of +/- 3.3V in order to provided reverse voltagr protection. The digital outputs have a current limit of 5mA per channel. 

### Indicator LEDs

There are three indicator LEDs, 1 green, 1 red and 1 yellow.
The green LED indicates status of any ongoing communication between host and the device. The red LED indicates any error which has occured in the device. The yello LED indicates that a firmware upgrade is going on the device.

### MCU

The microcontroller used in the device is CC2340R52 (https://www.ti.com/product/CC2340R5/part-details/CC2340R52E0RGER) which is an ARM Cortex-M0+ MCU with 512 KB FLASH and 36 KB RAM.

### UART, I2C and SPI interfaces

The device provides an SPI, I2C and a UART interface which can be used by the user to transfer bytes to external devices under test.

## Software block diagram

![alt text](<images/bluetooth-daq-design-Software Block Diagram.drawio.png>)

### 