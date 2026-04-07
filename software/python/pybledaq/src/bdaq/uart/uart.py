from ..core.core import Core
from enum import Enum

class UART:

    class parity(Enum):
        NONE = 0
        EVEN = 1
        ODD = 2
    
    class stop_bits(Enum):
        ONE = 0
        TWO = 1

    def __init__(self, core: Core):
        self.core: Core = core
    
    def configure( self, baud_rate: int, stop_bits: UART.stop_bits, parity: UART.parity ):

        self.core.write_parameters_last(["UART_PHY_CONTROL_baudrate",
                                         "UART_PHY_CONTROL_stopbits",
                                         "UART_PHY_CONTROL_parity"],
                                         [baud_rate, stop_bits.value, parity.value])
    
    def write( self, data: bytearray ):

        self.core.write_parameters_last(["UART_TRANSFER_CONTROL_transfer",
                                         "UART_TRANSFER_CONTROL_mode"],
                                        [0,0])
        
        write_index = 0

        self.core.write_parameters(["UART_TRANSFER_CONFIG_writesize"],[len(data)])

        for byte in data:

            self.core.write_parameters_last(["UART_WRITE_DATA_index",
                                             "UART_WRITE_DATA_byte"],
                                             [write_index, byte])

            write_index = write_index + 1

        self.core.write_parameters_last(["UART_TRANSFER_CONTROL_mode",
                                         "UART_TRANSFER_CONTROL_transfer"],
                                        [0,1]) 
        
    def read(self, size: int, timeout: int) -> bytearray:

        self.core.write_parameters(["UART_TRANSFER_CONFIG_readsize",
                                        "UART_TRANSFER_CONFIG_timeout"],
                                        [ size, timeout ])
            
        self.core.write_parameters_last(["UART_TRANSFER_CONTROL_transfer",
                                         "UART_TRANSFER_CONTROL_mode"],
                                        [1,1])

        read_count = int(self.core.read_parameters(["UART_READ_DATA_read_count"])[0])

        read_data = []

        for read_index in range( 0, read_count ):

            self.core.write_parameters(["UART_READ_DATA_index"],[read_index])

            read_data.append(self.core.read_parameters(["UART_READ_DATA_byte"])[0])
        
        return bytearray(read_data)
    
    def read_then_write( self, write_data : bytearray, read_size : int, read_timeout : int ) -> bytearray:

        write_index = 0

        self.core.write_parameters(["UART_TRANSFER_CONFIG_writesize"],[len(write_data)])

        for byte in write_data:

            self.core.write_parameters_last(["UART_WRITE_DATA_index",
                                             "UART_WRITE_DATA_byte"],
                                             [write_index, byte])

            write_index = write_index + 1


        self.core.write_parameters(["UART_TRANSFER_CONFIG_readsize",
                                        "UART_TRANSFER_CONFIG_timeout"],
                                        [read_size, read_timeout ])
            
        self.core.write_parameters_last(["UART_TRANSFER_CONTROL_transfer",
                                         "UART_TRANSFER_CONTROL_mode"],
                                        [1,2])

        read_count = int(self.core.read_parameters(["UART_READ_DATA_read_count"])[0])

        read_data = []

        for read_index in range( 0, read_count ):

            self.core.write_parameters(["UART_READ_DATA_index"],[read_index])

            read_data.append(self.core.read_parameters(["UART_READ_DATA_byte"])[0])
        
        return bytearray(read_data)

    def write_then_read( self, write_data : bytearray, read_size : int, read_timeout : int ) -> bytearray:

        write_index = 0

        self.core.write_parameters(["UART_TRANSFER_CONFIG_writesize"],[len(write_data)])

        for byte in write_data:

            self.core.write_parameters_last(["UART_WRITE_DATA_index",
                                             "UART_WRITE_DATA_byte"],
                                             [write_index, byte])

            write_index = write_index + 1

        self.core.write_parameters(["UART_TRANSFER_CONFIG_readsize",
                                        "UART_TRANSFER_CONFIG_timeout"],
                                        [read_size, read_timeout ])
            
        self.core.write_parameters_last(["UART_TRANSFER_CONTROL_transfer",
                                         "UART_TRANSFER_CONTROL_mode"],
                                        [1,3])

        read_count = int(self.core.read_parameters(["UART_READ_DATA_read_count"])[0])

        read_data = []

        for read_index in range( 0, read_count ):

            self.core.write_parameters(["UART_READ_DATA_index"],[read_index])

            read_data.append(self.core.read_parameters(["UART_READ_DATA_byte"])[0])
        
        return bytearray(read_data)