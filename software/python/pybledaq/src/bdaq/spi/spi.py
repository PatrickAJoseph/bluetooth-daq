class SPI:

    def __init__(self, core):
        self.core = core

    def configure(self, bit_rate: int, frame_format):

        bit_rate_reg = int(bit_rate / 10000)

        self.core.write_parameters_last(
            [
                "SPI_CONTROL_bit_rate",
                "SPI_CONTROL_frame_format"
            ],
            [
                bit_rate_reg,
                frame_format.value
            ]
        )

    def transfer(self, write_data: bytearray):

        transfer_size = len(write_data)

        # Write data
        for index, byte in enumerate(write_data):

            self.core.write_parameters(
                [
                    "SPI_WRITE_DATA_index",
                    "SPI_WRITE_DATA_byte"
                ],
                [
                    index,
                    byte
                ]
            )

        # Configure transfer
        self.core.write_parameters_last(
            [
                "SPI_CONTROL_transfer_size",
                "SPI_CONTROL_transfer"
            ],
            [
                transfer_size,
                1
            ]
        )

        # Read data
        read_data = []

        for i in range(transfer_size):

            self.core.write_parameters(
                ["SPI_READ_DATA_index"],
                [i]
            )

            byte = self.core.read_parameters(
                ["SPI_READ_DATA_byte"]
            )[0]

            read_data.append(byte)

        return bytearray(read_data)