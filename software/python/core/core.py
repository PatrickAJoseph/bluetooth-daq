
from .initiator import initiator
from .initiator import InterfaceType
from .parser import device

class core:

    initiator: initiator

    def __init__(self, configFile: str, interface: InterfaceType):

        try:
            self.initiator = initiator( configFile, interface )
        except Exception as error:
            print("Error in initializing the SSCP protocol core")
    
    def write_parameters( self, names: list[str], values: list[int] ):

        index = 0

        if( len(names) != len(values) ):

            print("write_parameters: Length of parameter name and parameter list must be equal !")

            raise ValueError("core: write_parameters: Length of parameter name and parameter list must be equal !")

            return

        try:

            for name in names:

                self.initiator.set_parameter_value_in_device( name, values[index] )
                index = index + 1
        
        except Exception as error:

            print("write_parameters: Error")

    def write_parameters_last( self, names: list[str], values : list[int] ):

        if( len(names) != len(values) ):

            print("Length of parameter names and parameter values must be equal.")

            raise ValueError("core: write_parameters_last: Length of parameter name and parameter values must be equal !")

            return

        for i in range( 0, len(names) - 1 ):

            try:

                self.initiator.set_parameter_value( names[i], values[i] )
            
            except Exception as error:

                print("write_parameters_last: Error")
        
        try:

            self.initiator.set_parameter_value_in_device( names[ len(names) - 1 ], values[ len(values) - 1 ]  )
        
        except Exception as error:

            print("write_parameters_last: Error")
    
    def read_parameters( self, names: list[str] ) -> list[int]:

        regNames = []

        for name in names:
            self.initiator.device.get_parameter_register(name).name
        
        uniqueRegNames = list(set(regNames))

        for regName in uniqueRegNames:

            self.initiator.read_register(regName)
        
        values = []

        for name in names:

            values.append(self.initiator.get_parameter_value(name))
        
        return values