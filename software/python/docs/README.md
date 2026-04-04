# Python interface for bluetoth DAQ

The python interface for controlling the bluetooth data acquisition system consists of the following subcomponents:

**Core**: Contains the SSCP protocol core and helper methods to perform basic/common operations.

**Socket**: Implements a socket connection between the DAQ control python script and any other application such as LabVIEW, thereby making interfacing to various applications easier.

**DIO**: The **dio** submodule is used to control the digital inputs/outputs of the DAQ.

**UART**: The **uart** submodule is used to send bytes, receive bytes and transceive bytes via the UART interface of the DAQ.

**SPI**: The **spi** submodule is used to transceive bytes via the SPI inteface of the DAQ.

**I2C**: The **i2c** submodule is used to transceive bytes via the I2C interface of the DAQ.

**hv_analog_in**: The high voltage analog input submodule is used to measure the DC voltage at the high voltage analog inputs of the DAQ.

**lv_analog_in**: The low voltage analog input submodule is used to measure the DC voltage at the low voltage inputs of the DAQ.

**analog_out**: The analog output submodule is used to control the analog outputs of the DAQ.

**current**: The current submodule is used to measure the current flowing through the current measurement inputs of the DAQ.

**resistance**: The resistance submodule is used to measure the resistance across the resistance input terminals of the DAQ.

**temperature**: The temperature submodule is used to measure the resistance of the thermistor connected across the thermistor input terminals of the DAQ and map it to a temperature value based on the resistance-vs-temperature curve provided by the user.

## bdaq

The bluetooth DAQ API is the high level module which abstracts all other submodules. All other submodules are only accessible through this module. This module consists of functions to initialize the bluetooth DAQ, set the communication interface (Serial/BLE) and other utility functions.

### members

>__bdaq.interface__

Defines the type of communication interface used to communicate with the DAQ.

**Permitted values** 

__bdaq.interface.SERIAL__

Select communication interface as serial interface. Device will interact with the host PC via RS-485 interface.

__bdaq.interface.BLE__

Select communication interface as BLE interface. Device will interact with the host PC via BLE.

### methods

>**bdaq**( *interface*: **bdaq.interface**, *id*: **int**, *comm_timeout*: **int**, *serial_number*: **int**)

Initializes the SSCP protocol stack for communicating with the DAQ with the required interface, device ID, communication interface timeout and device serial number. It also puts the device into the default state.

***Parameters***

*interface* : The communcation interface between the DAQ and the host PC. Can be either BLE or SERIAL.

*id* : The device ID of the DAQ. This number is useful for addressing a specific device among a number of devices connected to the same RS485 bus. It can take an integer value from 0 to 15. Passing any other values throws an exception.

*comm_timeout* : The communication timeout period in milli-seconds. If the DAQ does not respond within the specified timeout, a timeout exception is thrown.

*serial_number* : A 10-digit serial number which will be associated a DAQ during production. This number is important when communicating with the device via BLE.

## Core

The **core** submodule abstracts the SSCP (https://github.com/PatrickAJoseph/simple-system-control-protocol/tree/main/source/python) protocol APIs. 

>**bdaq.core**( *interface*: **initiator.InterfaceType**, *id*: **int**, *comm_timeout*: **int**, *port* : **str**, *serial_number*: **int**)

Initializes the SSCP protocol stack for communicating with the DAQ with the required interface, device ID, communication interface timeout and device serial number.

***Parameters***

*interface* : The communcation interface between the DAQ and the host PC. Can be either BLE or SERIAL.

*id* : The device ID of the DAQ. This number is useful for addressing a specific device among a number of devices connected to the same RS485 bus. It can take an integer value from 0 to 15. Passing any other values throws an exception.

*comm_timeout* : The communication timeout period in milli-seconds. If the DAQ does not respond within the specified timeout, a timeout exception is thrown.

*port* : The port identifier of the COM Port / TTY used for serial communication.

*serial_number* : A 10-digit serial number which will be associated a DAQ during production. This number is important when communicating with the device via BLE.

>**bdaq.core.write_parameters**(*names*: **str[]**, *values*: **int[]**)

Writes the list of parameter names with the list of parameter values. This function takes longer time to execute as each parameter will be written to the device.

***Parameters***

*names* : The list of parameter names to be written into the device.

*values* : The list of corresponding parameter values to be written in the device.

>**bdaq.core.write_parameters_last**(*names*: **str[]**, *values*: **int[]**)

Writes the list of parameter names with the list of parameter values. This loads all parameter values into memory and only then initiates a write to device operation. __Make sure that all the parameters mentioned in the list belong to the same device register__ (Refer to `ble-daq.yml` configuration file for more details) 

***Parameters***

*names* : The list of parameter names to be written into the device.

*values* : The list of corresponding parameter values to be written in the device.

>**bdaq.core.read_parameters**(*names* : **str[]**)

Reads the list of parameters from the device and returns a list containing their values

***Parameters***

*names* : The list of parameter names to be read from the device.

## DIO

The **D**igital **I**nput **O**utput module is used to control the digital inputs and digital outputs of the DAQ. This module allows reading and writing states of all pins at once as well as individually.

>**daq.dio.read_input**()

Returns the states of the digital input pins as a 16-bit integer.

>**daq.dio.read_output**()

Returns the states of the digital output pins as a 16-bit integer.

>**daq.dio.write_output**(*output* : **int**)

Writes the 16-bit output word to the digital outputs of the DAQ.

*Parameters*

*output* : The 16-bit output which has to be written to the digital output pins of the DAQ. The value of *output* must range from 0 to 65535. Any other values throws a *ValueError*.

>**bdaq.dio.set_output_pin_state**( *pin* : **int**, *state* : **Bool** )

Sets state of digital output *pin* to the assigned *state*. The *pin* can take values from 0 to 15. Any other values throws *ValueError*.

*Parameters*

*pin* : The pin number of the digital output which has to be controlled. Valid value of *pin* is from 0 to 15.

*state* : The state of the digital output pin.

>**bdaq.dio.get_output_pin_state**( *pin* : **int** )

Gets the state of the output *pin*. Returns __True__ ifoutput state high, else, returns __False__

*Parameters*

*pin* : The pin number in the digital output whose state has to be examined.

>**bdaq.dio.toggle_output_pin_state**( *pin* : **int** )

Toggles the state of the output *pin*.

*Parameters*

*pin* : The pin number in the digital output whose state has to be toggled.

>**bdaq.dio.get_input_pin_state**( *pin* : **int** )

Gets the state of the digital input *pin*. Returns __True__ if input state is high, else, returns __False__

*Parameters*

*pin* : The pin number in the digital input whose state has to be examined.

## UART

The UART submodule provides features to configure the user UART, send data and receive data from an external device. The current implementation supports a data length of only 8 bits.

### Types

>**dio.uart.stop_bits**

Defines the number of supported stop bits. The device only supports 1 and 2 stop bits.

*dio.uart.stop_bits.ONE* : Number of stop bits is 1.

*dio.uart.stop_bits.TWO* : Number of stop bits is 2.

>**dio.uart.parity**

Defines the type of parity for a UART frame.

*dio.uart.parity.NONE* : Parity is set to none.

*dio.uart.parity.EVEN* : Parity is set to even.

*dio.uart.parity.ODD* : Parity is set to odd.

### Methods

>**bdaq.uart.configure**( *baud_rate* : **int**, *stop_bits* : **bdaq.uart.stop_bits**, *parity* : **bdaq.uart.parity** )

Configures the user UART with the specified baud rate, stop bits and parity.

*baud_rate* : The baud rate at which the UART bits have to be transferred. Valid baud rate is from 300 bps to 921600 bps. Values beyond this range will return error.

*stop_bits* : The number of stop bits. The stop bits must be mentioned via the enum.

*parity* : The parity bit settings. This argument must take one of the values from the __bdaq.uart.parity__ enum.

>**bdaq.uart.set_read_timeout**( *timeout* : **int** )

Sets the UART transfer timeout in milliseconds. Required for UART read operations. Timeout value can range from 0 to 60000. Values other than that will throw *ValueError*.

*timeout* : The UART read timeout specified in milli-seconds.

>**bdaq.uart.write**( *data* : **bytearray** )

Sends the bytes in *data* over the UART interface.

*data* : The data bytes to be sent over the UART TX line.

>**bdaq.uart.read**( *size* : **int**, *timeout* : **int** )

Reads the specified number of bytes (i.e.) *size* available in the UART RX line within the mentioned *timeout* period.

*size* : The number of bytes to be read from the UART RX line.

*timeout* : The timeout duration for the read operation along the UART RX line ( in __milliseconds__ )

>**bdaq.uart.read_then_write**( *write_data* : **bytearray**, *read_size* : **int**, *read_timeout* : **int** )

Reads the number of bytes from the UART Rx line within the mentioned timeout duration and when writes the specified bytes to the UART Tx line.

*write_data* : Byte array containing the btyes to be written via the UART Tx line.

*read_size* : The number of bytes to be read from the UART Rx line.

*read_timeout* : The timeout duration for the read operation along the UART Rx line ( in __milliseconds__ ).

>**bdaq.uart.write_then_read**( *write_data* : **bytearray**, *read_size* : **int**, *read_timeout* : **int** )

Writes the mentioned bytes along the UART Tx line and reads the bytes available along the UART Rx line within the specified timeout interval.

*write_data* : Byte array containing the btyes to be written via the UART Tx line.

*read_size* : The number of bytes to be read from the UART Rx line.

*read_timeout* : The timeout duration for the read operation along the UART Rx line ( in __milliseconds__ ).

## SPI

The SPI submodules provides features to configure the SPI controller and transfer bytes. The SPI module only supports MSB first transfers. LSB first transfers are not supported.

### Types

>**bdaq.spi.frame_format**

The SPI transfer frame format.

*bdaq.spi.frame_format.CPOL_0_CPHA_0* : SPI mode 0, Clock polarity is 0 and Clock phase is 0.

*bdaq.spi.frame_format.CPOL_0_CPHA_1* : SPI mode 0, Clock polarity is 0 and Clock phase is 1.

*bdaq.spi.frame_format.CPOL_1_CPHA_0* : SPI mode 0, Clock polarity is 1 and Clock phase is 0.

*bdaq.spi.frame_format.CPOL_1_CPHA_1* : SPI mode 0, Clock polarity is 1 and Clock phase is 1.

### Methods

>**bdaq.spi.configure**( *bit_rate* : **int**, *frame_format* : **bdaq.spi.frame_format** )

*bit_rate* : The frequency at which the data bits have to be trandferred. The *bit_rate* must a multiple of 10k and can range from 100kbps to 2 Mbps. Any other values results in *ValueError*.

*frame_format* : The frame format must take one of the values from __bsaq.spi.frame_format* enum.

>**bdaq.spi.transfer**( *write_data* : **bytearray** )

Sends over the bytes specified in the *write_data* byte array via the MOSI line and returns the read bytes via the MISO line in __bytearray__ format.

## I2C

The I2C submodule supports the I2C read and write operations to an I2C peripheral and configuration of the I2C peripheral. The supported modes are standard and fast mode and 7-bit addressing mode.

### Types

>**bdaq.i2c.mode**

Indicates whether transfer mode is standard or fast mode.

*bdaq.i2c.mode.standard* : Transfers bits at 100 kHz.

*bdaq.i2c.mode.fast* : Transfers bits at 400 kHz.

### Methods

>**bdaq.i2c.configure**( *mode* : **bdaq.i2c.mode**, *address* : **int** )

Configures the I2C controller with the required transfer mode and the target peripheral address.

*Parameters*

*mode* : The transfer mode must take arguments only from the bdaq.i2c.mode enum.

*address* : The supported target addresses are from 0 to 127. Passing any other value returns in a *ValueError*.

>**bdaq.i2c.transfer**( *write_data* : **bytearray**, *read_size* : **int** )

Sends over the bytes specified in the *write_data* byte array via the SDA line and reads *read_size* number of bytes from the peripheral via the SDA line.