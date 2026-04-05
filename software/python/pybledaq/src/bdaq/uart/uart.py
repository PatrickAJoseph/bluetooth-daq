import core

class UART:
    def __init__(self, core):
        self.core = core
        
    def set_physical_control_reg( self, baudrate: int, stop_bit: int, parity: int):
        self.core.write_parameters_last([
                                        "UART_PHY_CONTROL_baudrate",
                                         "UART_PHY_CONTROL_stop_bits",
                                         "UART_PHY_CONTROL_parity"], 
                                         [baudrate,
                                          stop_bit,
                                          parity
                                          ])
    def set_transfer_config_reg( self, read_size: int, write_size: int, timeout: int):
        self.core.write_parameters_last([
                                        "UART_TRANSFER_CONFIG_readsize",
                                         "UART_TRANSFER_CONFIG writesize",
                                         "UART_TRANSFER_CONFIG_timeout"]
                                         [read_size,
                                          write_size,
                                          timeout
                                          ])
        
    def read_data(self, index: int, data_byte: int, data_count: int) -> list[int]:
        self.set_physical_control_reg(115200, 1, 0)
        self.set_transfer_config_reg(data_count, 0, 1000)

        return self.core.read_parameter("UART_READ_DATA")
    
    def write_data(self, index: int, data: list[int]):
        self.set_physical_control_reg(115200, 1, 0)
        self.set_transfer_config_reg(0, len(data), 1000)

        self.core.write_parameter("UART_WRITE_DATA", data)