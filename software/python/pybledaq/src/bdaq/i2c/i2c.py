import core

class I2C:
    def __init__(self, core):
        self.core = core

    def set_control_reg( self, fast_mode: int, address: int, timeout: int, ):
        self.core.write_parameters_last([
                                        "I2C_CONTROL_fast_mode_enable",
                                         "I2C_CONTROL_address",
                                         "I2C_CONTROL_timeout"], 
                                         [fast_mode,
                                          address,
                                          timeout
                                          ])
    def set_transfer_config_reg( self, read_size: int, write_size: int, status: int, transfer: int):
        self.core.write_parameters_last([
                                        "I2C_TRANSFER_CONFIG_readsize",
                                         "I2C_TRANSFER_CONFIG writesize"], 
                                         [read_size,
                                          write_size,
                                            status,
                                            transfer
                                          ])
        
    def read_data(self, index: int, data_count: int) -> list[int]:
        self.set_control_reg(0, 0x0, 1000)
        self.set_transfer_config_reg(data_count, 0, 0, 1)

        return self.core.read_parameter("I2C_READ_DATA_REG")

    def write_data(self, index: int, data: list[int]):
        self.set_control_reg(0, 0x0, 1000)
        self.set_transfer_config_reg(0, len(data), 0, 1)

        self.core.write_parameter("I2C_WRITE_DATA_REG", data)