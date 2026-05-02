import bdaq
import time

from bdaq.spi import SPI

x = bdaq.bdaq( 0, 0, 100, 'COM13', 1 )

x.spi.configure( bitRate = 500000,
                   cs_polarity = SPI.polarity.ACTIVE_LOW,
                   frame_format = SPI.frame_format.POL1_PHA0)

for i in range(0,1000):
    resp = x.spi.transfer(bytearray([0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07]))