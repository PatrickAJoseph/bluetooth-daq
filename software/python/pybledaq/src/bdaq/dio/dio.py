from ..core.core import Core

class DIO:
    def __init__(self, core):
        self.core: Core = core

    def read_input(self) -> int:

        values = self.core.read_parameters(["GPIO_read_value"])

        return int(values[0])

    def read_output(self) -> int:

        values = self.core.read_parameters(["GPIO_write_value"])

        return int(values[0])

    def write_output(self, value: int):
        self.core.write_parameters(["GPIO_write_value"], [value])
    
    def set_output_pin_state( self, pin: int, state: bool ):
        self.core.write_parameters_last([
                                        "GPIO_PINCTRL_input_select",
                                         "GPIO_PINCTRL_pin_index",
                                         "GPIO_PINCTRL_read",
                                         "GPIO_PINCTRL_write",
                                         "GPIO_PINCTRL_toggle",
                                         "GPIO_PINCTRL_value"], 
                                         [0, 
                                          pin,
                                          0,
                                         1,
                                         0,
                                         int(state)])
        
    def get_output_pin_state( self, pin: int ) -> bool:

        self.core.write_parameters_last([
                                        "GPIO_PINCTRL_input_select",
                                         "GPIO_PINCTRL_pin_index",
                                         "GPIO_PINCTRL_read",
                                         "GPIO_PINCTRL_write",
                                         "GPIO_PINCTRL_toggle"], 
                                         [0, 
                                          pin,
                                          1,
                                         0,
                                         0])

        return bool(int(self.core.read_parameter("GPIO_PINCTRL_value")))

    def toggle_output_pin_state( self, pin: int ) -> bool:

        self.core.write_parameters_last([
                                        "GPIO_PINCTRL_input_select",
                                         "GPIO_PINCTRL_pin_index",
                                         "GPIO_PINCTRL_read",
                                         "GPIO_PINCTRL_write",
                                         "GPIO_PINCTRL_toggle"], 
                                         [0, 
                                          pin,
                                          0,
                                         0,
                                         1])

    def get_input_pin_state( self, pin: int ) -> bool:

        self.core.write_parameters_last([
                                        "GPIO_PINCTRL_input_select",
                                         "GPIO_PINCTRL_pin_index",
                                         "GPIO_PINCTRL_read",
                                         "GPIO_PINCTRL_write",
                                         "GPIO_PINCTRL_toggle"], 
                                         [1, 
                                          pin,
                                          1,
                                         0,
                                         0])

        return bool(int(self.core.read_parameters(["GPIO_PINCTRL_value"])[0]))