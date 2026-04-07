from .core.core import Core
from .dio.dio import DIO
from .uart.uart import UART
from .spi.spi import SPI
from .i2c.i2c import I2C

class bdaq:
    def __init__(self, interface, id, comm_timeout, port, serial_number):
        self.core = Core(interface, id, comm_timeout, port, serial_number)

        self.dio = DIO(self.core)
        self.uart = UART(self.core)
        self.spi = SPI(self.core)
        self.i2c = I2C(self.core)