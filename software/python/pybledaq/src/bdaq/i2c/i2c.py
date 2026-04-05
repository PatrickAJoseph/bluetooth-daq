import core
from enum import Enum

class I2C:

    class mode(Enum):
        STANDARD = 0
        FAST = 1

    def __init__(self, core: core):
        self.core :core = core
    
    def configure( self, mode: I2C.mode, address :int, timeout: int ):

        self.core.write_parameters_last(["I2C_CONTROL_fast_mode_enable",
                                         "I2C_CONTROL_address",
                                         "I2C_CONTROL_timeout"],
                                         [ mode.value, address, timeout ])
    
    def transfer( self, write_data: bytearray, read_size: int ) -> list[int]:

        for write_index in range(0, len(write_data)):

            self.core.write_parameters_last(["I2C_WRITE_DATA_byte",
                                             "I2C_WRITE_DATA_index"],
                                             [write_data[write_index], write_index])

        self.core.write_parameters_last(["I2C_TRANSFER_CONFIG_readsize",
                                         "I2C_TRANSFER_CONFIG_writesize",
                                         "I2C_TRANSFER_CONFIG_transfer"],
                                         [read_size,
                                          len(write_data),
                                          0]
                                         )
        
        read_data = []

        for read_index in range( 0, read_size ):

            self.core.write_parameters(["I2C_READ_DATA_index", read_index])

            read_data.append(self.core.read_parameters(["I2C_READ_DATA_byte"])[0])
        
        return read_data