import bdaq
import time

from bdaq.i2c import I2C

x = bdaq.bdaq( 0, 0, 1000, 'COM13', 1 )

x.i2c.configure( mode = I2C.mode.STANDARD, address = int(0x3C), timeout = 10000 )

# Display OFF
write_data = [int(0x00), int(0xAE)]
x.i2c.transfer(bytearray(write_data), 0)

# Clock divide ratio / oscillator frequency
write_data = [int(0x00), int(0xD5), int(0x80)]
x.i2c.transfer(bytearray(write_data), 0)

# Multiplex ratio (1/64)
write_data = [int(0x00), int(0xA8), int(0x3F)]
x.i2c.transfer(bytearray(write_data), 0)

# Display offset
write_data = [int(0x00), int(0xD3), int(0x00)]
x.i2c.transfer(bytearray(write_data), 0)

# Start line = 0
write_data = [int(0x00), int(0x40)]
x.i2c.transfer(bytearray(write_data), 0)

# Charge pump enable
write_data = [int(0x00), int(0x8D), int(0x14)]
x.i2c.transfer(bytearray(write_data), 0)

# Memory addressing mode = horizontal
write_data = [int(0x00), int(0x20), int(0x00)]
x.i2c.transfer(bytearray(write_data), 0)

# Segment remap
write_data = [int(0x00), int(0xA1)]
x.i2c.transfer(bytearray(write_data), 0)

# COM scan direction remap
write_data = [int(0x00), int(0xC8)]
x.i2c.transfer(bytearray(write_data), 0)

# COM pins hardware configuration
write_data = [int(0x00), int(0xDA), int(0x12)]
x.i2c.transfer(bytearray(write_data), 0)

# Contrast control
write_data = [int(0x00), int(0x81), int(0xCF)]
x.i2c.transfer(bytearray(write_data), 0)

# Pre-charge period
write_data = [int(0x00), int(0xD9), int(0xF1)]
x.i2c.transfer(bytearray(write_data), 0)

# VCOMH deselect level
write_data = [int(0x00), int(0xDB), int(0x40)]
x.i2c.transfer(bytearray(write_data), 0)

# Resume to RAM content display
write_data = [int(0x00), int(0xA4)]
x.i2c.transfer(bytearray(write_data), 0)

# Normal display (not inverted)
write_data = [int(0x00), int(0xA6)]
x.i2c.transfer(bytearray(write_data), 0)

# Disable scrolling
write_data = [int(0x00), int(0x2E)]
x.i2c.transfer(bytearray(write_data), 0)

# Display ON
write_data = [int(0x00), int(0xAF)]
x.i2c.transfer(bytearray(write_data), 0)

for i in range(0,1024):
    x.i2c.transfer(bytearray([int(0x40), int( 0 )]), 0)
    print("Displaying: {_index} out of 1024".format( _index = i ))

for i in range(0,1024):
    x.i2c.transfer(bytearray([int(0x40), int( 1 << (7 - (i%8)) )]), 0)
    print("Displaying: {_index} out of 1024".format( _index = i ))

for i in range(0,1024):
    x.i2c.transfer(bytearray([int(0x40), int( (1 << (i%8)) - 1 )]), 0)
    print("Displaying: {_index} out of 1024".format( _index = i ))

for i in range(0,1024):
    x.i2c.transfer(bytearray([int(0x40), int( (1 << ( 7 - (i%8) ) ) - 1 )]), 0)
    print("Displaying: {_index} out of 1024".format( _index = i ))