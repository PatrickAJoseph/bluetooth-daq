class I2C:

    def __init__(self, core):
        self.core = core

    def configure(self, address, fast_mode=False, timeout=1000):

        self.core.write_parameters_last(
            [
                "I2C_CONTROL_fast_mode_enable",
                "I2C_CONTROL_address",
                "I2C_CONTROL_timeout"
            ],
            [
                int(fast_mode),
                address,
                timeout
            ]
        )

    def transfer(self, write_data: bytearray, read_size: int):

        write_size = len(write_data)

        # load write buffer
        for index, byte in enumerate(write_data):

            self.core.write_parameters(
                [
                    "I2C_WRITE_DATA_index",
                    "I2C_WRITE_DATA_byte"
                ],
                [
                    index,
                    byte
                ]
            )

        # trigger transfer
        self.core.write_parameters_last(
            [
                "I2C_TRANSFER_CONFIG_readsize",
                "I2C_TRANSFER_CONFIG_writesize",
                "I2C_TRANSFER_CONFIG_transfer"
            ],
            [
                read_size,
                write_size,
                1
            ]
        )

        # read response
        data = []

        for i in range(read_size):

            self.core.write_parameters(
                ["I2C_READ_DATA_index"],
                [i]
            )

            byte = self.core.read_parameters(
                ["I2C_READ_DATA_byte"]
            )[0]

            data.append(byte)

        return bytearray(data)