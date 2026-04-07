import bdaq
from bdaq.uart import UART

x = bdaq.bdaq( 0, 0, 10000, 'COM13', 1 )

x.uart.configure(baud_rate = 115200, stop_bits = UART.stop_bits.ONE, parity = UART.parity.NONE)
x.uart.write( bytearray("TEST_STRING", encoding = 'utf-8') )
read_data = x.uart.write_then_read( write_data = bytearray("TEST_STRING_WRITE_THEN_READ\r\n", encoding = 'UTF-8'), 
                                    read_size = 32, read_timeout = 10000 )
print(read_data)

read_data = x.uart.read_then_write( write_data = bytearray("TEST_STRING_READ_THEN_WRITE\r\n", encoding = 'UTF-8'), 
                                    read_size = 32, read_timeout = 10000 )
print(read_data)