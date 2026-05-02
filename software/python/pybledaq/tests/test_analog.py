import bdaq
import time

from bdaq.analog import Analog

x = bdaq.bdaq( 0, 0, 100, 'COM13', 1 )

x.analog.set_output(3,2.5)