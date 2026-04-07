
import bdaq
import time

# Open a serial connection to the device.

x = bdaq.bdaq(0, 0, 10000, 'COM13', 1)

# Write a 4-bit word and check the outputs.

for i in range(0,16):
    x.dio.write_output(i)
    output_word = x.dio.read_output()

    print("Output word: {_word}".format(_word = hex(output_word)))

    time.sleep(0.25)

start_time = time.perf_counter()

while( ( time.perf_counter() - start_time ) < 1.0 ):
    input_word = x.dio.read_input()
    print("Input word: {_word}".format(_word=hex(input_word)))
    time.sleep(0.1)

for i in range(0,4):
    x.dio.set_output_pin_state(i, False)
    time.sleep(0.1)

for i in range(0,4):
    x.dio.set_output_pin_state(i, True)
    time.sleep(0.1)

for i in range(0,4):
    x.dio.set_output_pin_state(i, False)
    time.sleep(0.1)

for i in range(0,4):
    x.dio.set_output_pin_state(i, True)
    time.sleep(0.1)

# Get pin state and reflect it at output pin.

start_time = time.perf_counter()

while( ( time.perf_counter() - start_time ) < 10.0 ):
    pin_state = x.dio.get_input_pin_state(0)
    print("Input {_index} state: {_value}".format( _index = 0, _value = pin_state))