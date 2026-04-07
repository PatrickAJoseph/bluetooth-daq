
from .initiator import initiator
from .initiator import InterfaceType
import yaml
import os

class Core:

    def __init__(self, interface, id, comm_timeout, port, serial_number):
        self.interface = interface
        self.id = id
        self.timeout = comm_timeout
        self.serial_number = serial_number
        self.initiator : initiator.initiator
        self.port = port

        read_file_path = os.path.join(os.path.dirname(__file__), "bluetooth_daq.yml")

        with open(read_file_path,'r') as file:

            fileData = yaml.safe_load(file)

            fileData['defconfig']['device_number'] = str(id)
            fileData['defconfig']['interface_timeout_ms'] = str(comm_timeout)

            if( interface == 0 ):
                fileData['defconfig']['serial_port'] = str(port)
            else:
                fileData['defconfig']['device_serial_number'] = str(serial_number)

            with open('bluetooth_daq_config.yml', 'w') as writeFile:

                yaml.dump( fileData, writeFile )

            if( interface == 0 ):

                self.initiator = initiator('bluetooth_daq_config.yml', InterfaceType.SERIAL)

    def read_parameters(self, names):
        
        regNames = []

        for name in names:

            regNames.append(self.initiator.device.get_parameter_register(name).name)
        
        uniqueRegNames = list(set(regNames))

        for name in uniqueRegNames:

            self.initiator.read_register(name)

        parameterValues = []

        for name in names:

            parameterValues.append( int( self.initiator.get_parameter_value(name) ) )

        return parameterValues

    def write_parameters(self, names, values):
        
        index = 0

        for name in names:

            self.initiator.set_parameter_value_in_device(name, values[index])

            index = index + 1
    
    def write_parameters_last(self, names: list[str], values: list[int] ):

        index = 0

        for i in range(0, len(names) - 1):

            self.initiator.set_parameter_value( names[i], values[i] )
        
        self.initiator.set_parameter_value_in_device( names[len(names) - 1], values[len(values) - 1] )