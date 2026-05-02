
import bdaq
import time

# Open a serial connection to the device.

x = bdaq.bdaq(0, 0, 500, 'COM13', 1)

# Write a 4-bit word and check the outputs.

for i in range(0,8):
    x.dio.write_output(1 << i)
    output_word = x.dio.read_output()

    print("Output word: {_word}".format(_word = hex(output_word)))

    time.sleep(0.5)

start_time = time.perf_counter()

while( ( time.perf_counter() - start_time ) < 30.0 ):
    input_word = x.dio.read_input()
    print("Input word: {_word}".format(_word=hex(input_word)))
    time.sleep(0.1)