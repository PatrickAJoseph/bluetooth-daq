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

>**bdaq.core**( *interface*: **initiator.InterfaceType**, *id*: **int**, *comm_timeout*: **int**, *serial_number*: **int**)

Initializes the SSCP protocol stack for communicating with the DAQ with the required interface, device ID, communication interface timeout and device serial number.

***Parameters***

*interface* : The communcation interface between the DAQ and the host PC. Can be either BLE or SERIAL.

*id* : The device ID of the DAQ. This number is useful for addressing a specific device among a number of devices connected to the same RS485 bus. It can take an integer value from 0 to 15. Passing any other values throws an exception.

*comm_timeout* : The communication timeout period in milli-seconds. If the DAQ does not respond within the specified timeout, a timeout exception is thrown.

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