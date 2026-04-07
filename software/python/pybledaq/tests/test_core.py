import bdaq
import time

# Open a serial connection to the device.

x = bdaq.bdaq(0, 0, 10000, 'COM13', 1)

# Set initial LED state to true.

state = True

# Toggle digital output 0 ten times.

for i in range(0,10):
    x.core.write_parameters(["GPIO_write_value"],[int(state)])
    state = False if state is True else True
    time.sleep(0.1)

    # Set digital output 1 and wait for 0.25 seconds.

    x.core.write_parameters_last(["GPIO_PINCTRL_input_select",
                             "GPIO_PINCTRL_pin_index",
                             "GPIO_PINCTRL_read",
                             "GPIO_PINCTRL_write",
                             "GPIO_PINCTRL_toggle",
                             "GPIO_PINCTRL_value"],
                            [0,
                             1,
                             0,
                             1,
                             0,
                             1])

    time.sleep(0.25)

    # Clear digital output 1 and wait for 0.25 seconds.

    x.core.write_parameters_last(["GPIO_PINCTRL_input_select",
                             "GPIO_PINCTRL_pin_index",
                             "GPIO_PINCTRL_read",
                             "GPIO_PINCTRL_write",
                             "GPIO_PINCTRL_toggle",
                             "GPIO_PINCTRL_value"],
                            [0,
                             1,
                             0,
                             1,
                             0,
                             0])

    time.sleep(0.25)

# Read digital input 0 state.

for i in range(0,1000):

    print( x.core.read_parameters(["GPIO_read_value"])[0] )

    time.sleep(0.01)