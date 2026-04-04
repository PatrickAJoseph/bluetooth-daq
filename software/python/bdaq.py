
from .core import core
from .core.initiator import initiator
from enum import Enum

import yaml

class bdaq:

    core: core

    class interface (Enum):
        SERIAL = 0
        BLE = 1

    def __init__( self, interface: bdaq.interface, 
            id: int, 
            comm_timeout: int,
            port: str, 
            serial_number: int):
        
        # Create a copy of ble-daq.yml as we don't want the
        # original configuration file to be corrupted.

        with open('utils/ble-daq.yml') as readFile:

            with open('utils/config.yml') as writeFile:

                for line in readFile:
                    writeFile.write(line)

        # Make required configuration changes for the session.

        with open('utils/config.yml', 'w') as file:

            fileData = yaml.safe_load(file)

            fileData['defconfig']['serial_port'] = port
            fileData['defconfig']['device_number'] = id

            if( interface == bdaq.interface.SERIAL ):
                fileData['defconfig']['interface_timeout_ms'] = comm_timeout
            elif( interface == bdaq.interface.BLE ):
                fileData['defconfig']['device_serial_number'] = serial_number
            
            yaml.dump(fileData, file)
        
        #TODO: Open a new 'core' instance.

        try:

            self.core( 'utils/config.yml', initiator.InterfaceType.SERIAL if interface is bdaq.interface.SERIAL else initiator.InterfaceType.BLE )

        except Exception as error:

            print("bdaq: init: Failed to initialize the core for the bluetooth module")

        #TODO: Initialize DAQ to default state.