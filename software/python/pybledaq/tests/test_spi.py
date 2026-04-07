import bdaq
import time

from bdaq.spi import SPI

x = bdaq.bdaq( 0, 0, 10000, 'COM13', 1 )

x.spi.configure( bitRate = 1000000,
                   cs_polarity = SPI.polarity.ACTIVE_LOW,
                   frame_format = SPI.frame_format.POL1_PHA0)

for j in range(0,128):

    i = j%16

    write_data = [16*i,16*i+1,16*i+2,16*i+3,16*i+4,
                  16*i+5,16*i+6,16*i+7,16*i+8,16*i+9,
                  16*i+10,16*i+11,16*i+12,16*i+13,16*i+14,16*i+15]

    read_data = x.spi.transfer(bytearray(write_data))

    print(read_data)


print(read_data)