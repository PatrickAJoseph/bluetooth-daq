from ..core.core import Core
from enum import Enum

class Analog:

    def __init__(self, core: Core):
        self.core: Core = core
    
    def set_output(self, index: int, voltage: float):
        _voltage: int = int( voltage * 1000.0 )

        if( index > 3 ):
            raise ValueError("Analog output channel index > 3.")
        
        if ( voltage < -10.0 ) or ( voltage > 10.0 ):
            raise ValueError("Analog output voltage must be within +/- 10V.")

        self.core.write_parameters(["DAC_channel_index","DAC_channel_voltage"],
                                   [index, _voltage])