from enum import Enum


class UARTParity(Enum):
    NONE = 0
    ODD = 1
    EVEN = 2


class UARTStopBits(Enum):
    ONE = 0
    TWO = 1


class UARTTransferMode(Enum):
    WRITE = 0
    READ = 1
    READ_THEN_WRITE = 2
    WRITE_THEN_READ = 3


class UART:

    def __init__(self, core):
        self.core = core

    # --------------------------------
    # Configure UART
    # --------------------------------
    def configure(self, baud_rate, stop_bits, parity):

        self.core.write_parameters_last(
            [
                "UART_PHY_CONTROL_baudrate",
                "UART_PHY_CONTROL_stopbits",
                "UART_PHY_CONTROL_parity"
            ],
            [
                baud_rate,
                stop_bits.value,
                parity.value
            ]
        )

    # --------------------------------
    # Write
    # --------------------------------
    def write(self, data: bytearray, timeout: int = 1000):

        size = len(data)

        # configure transfer
        self.core.write_parameters_last(
            [
                "UART_TRANSFER_CONFIG_readsize",
                "UART_TRANSFER_CONFIG_writesize",
                "UART_TRANSFER_CONFIG_timeout"
            ],
            [
                0,
                size,
                timeout
            ]
        )

        # write data bytes
        for index, byte in enumerate(data):
            self.core.write_parameters(
                [
                    "UART_WRITE_DATA_index",
                    "UART_WRITE_DATA_byte"
                ],
                [
                    index,
                    byte
                ]
            )

        # trigger transfer
        self.core.write_parameters_last(
            [
                "UART_TRANSFER_CONTROL_mode",
                "UART_TRANSFER_CONTROL_transfer"
            ],
            [
                UARTTransferMode.WRITE.value,
                1
            ]
        )

    # --------------------------------
    # Read
    # --------------------------------
    def read(self, size: int, timeout: int = 1000):

        # configure transfer
        self.core.write_parameters_last(
            [
                "UART_TRANSFER_CONFIG_readsize",
                "UART_TRANSFER_CONFIG_writesize",
                "UART_TRANSFER_CONFIG_timeout"
            ],
            [
                size,
                0,
                timeout
            ]
        )

        # trigger read
        self.core.write_parameters_last(
            [
                "UART_TRANSFER_CONTROL_mode",
                "UART_TRANSFER_CONTROL_transfer"
            ],
            [
                UARTTransferMode.READ.value,
                1
            ]
        )

        # read bytes
        data = []

        for i in range(size):

            # set index
            self.core.write_parameters(
                ["UART_READ_DATA_index"],
                [i]
            )

            # read byte
            byte = self.core.read_parameters(
                ["UART_READ_DATA_byte"]
            )[0]

            data.append(byte)

        return bytearray(data)

    # --------------------------------
    # Write Then Read
    # --------------------------------
    def write_then_read(self, write_data, read_size, timeout=1000):

        write_size = len(write_data)

        # configure transfer
        self.core.write_parameters_last(
            [
                "UART_TRANSFER_CONFIG_readsize",
                "UART_TRANSFER_CONFIG_writesize",
                "UART_TRANSFER_CONFIG_timeout"
            ],
            [
                read_size,
                write_size,
                timeout
            ]
        )

        # write bytes
        for index, byte in enumerate(write_data):
            self.core.write_parameters(
                [
                    "UART_WRITE_DATA_index",
                    "UART_WRITE_DATA_byte"
                ],
                [
                    index,
                    byte
                ]
            )

        # trigger transfer
        self.core.write_parameters_last(
            [
                "UART_TRANSFER_CONTROL_mode",
                "UART_TRANSFER_CONTROL_transfer"
            ],
            [
                UARTTransferMode.WRITE_THEN_READ.value,
                1
            ]
        )

        # read response
        data = []

        for i in range(read_size):

            self.core.write_parameters(
                ["UART_READ_DATA_index"],
                [i]
            )

            byte = self.core.read_parameters(
                ["UART_READ_DATA_byte"]
            )[0]

            data.append(byte)

        return bytearray(data)

    # --------------------------------
    # Read Then Write
    # --------------------------------
    def read_then_write(self, write_data, read_size, timeout=1000):

        write_size = len(write_data)

        self.core.write_parameters_last(
            [
                "UART_TRANSFER_CONFIG_readsize",
                "UART_TRANSFER_CONFIG_writesize",
                "UART_TRANSFER_CONFIG_timeout"
            ],
            [
                read_size,
                write_size,
                timeout
            ]
        )

        for index, byte in enumerate(write_data):
            self.core.write_parameters(
                [
                    "UART_WRITE_DATA_index",
                    "UART_WRITE_DATA_byte"
                ],
                [
                    index,
                    byte
                ]
            )

        self.core.write_parameters_last(
            [
                "UART_TRANSFER_CONTROL_mode",
                "UART_TRANSFER_CONTROL_transfer"
            ],
            [
                UARTTransferMode.READ_THEN_WRITE.value,
                1
            ]
        )

        data = []

        for i in range(read_size):

            self.core.write_parameters(
                ["UART_READ_DATA_index"],
                [i]
            )

            byte = self.core.read_parameters(
                ["UART_READ_DATA_byte"]
            )[0]

            data.append(byte)

        return bytearray(data)