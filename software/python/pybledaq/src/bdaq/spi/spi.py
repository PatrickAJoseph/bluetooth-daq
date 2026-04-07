from ..core.core import Core
from enum import Enum

class SPI:

    class frame_format(Enum):
        POL0_PHA0 = 0
        POL0_PHA1 = 1
        POL1_PHA0 = 2
        POL1_PHA1 = 3
    
    class polarity(Enum):
        ACTIVE_LOW = 0
        ACTIVE_HIGH = 1

    def __init__(self, core: Core):
        self.core : Core = core
    
    def configure(self, bitRate: int, frame_format: SPI.frame_format, cs_polarity: SPI.polarity):
        
        self.core.write_parameters_last(["SPI_CONTROL_bit_rate",
                                         "SPI_CONTROL_frame_format",
                                         "SPI_CONTROL_transfer_size",
                                         "SPI_CONTROL_cs_polarity",
                                         "SPI_CONTROL_transfer",
                                         "SPI_CONTROL_status"],
                                         [int(bitRate/10000),
                                          frame_format.value,
                                          0,
                                          cs_polarity.value,
                                          0,
                                          0])
    
    def transfer( self, write_data: bytearray ) -> bytearray:

        write_index = 0

        #self.core.write_parameters(["SPI_CONTROL_transfer"],[0])

        self.core.write_parameters_last(["SPI_CONTROL_transfer_size",
                                    "SPI_CONTROL_transfer"], 
                                    [len(write_data),
                                     0])

        for data in write_data:

            self.core.write_parameters_last(["SPI_WRITE_DATA_index",
                                             "SPI_WRITE_DATA_byte"],
                                             [write_index,
                                              int(data)])
            
            write_index = write_index + 1
        
        self.core.write_parameters(["SPI_CONTROL_transfer"],[1])

        read_data = []

        for i in range( 0, len(write_data) ):

            self.core.write_parameters(["SPI_READ_DATA_index"],[i])
            read_data.append(int(self.core.read_parameters(["SPI_READ_DATA_byte"])[0]))
        
        return bytearray(read_data)