import bdaq
import time
import matplotlib.pyplot as plt
import numpy as np

def simple_moving_average(data, window_size):
    weights = np.ones(window_size) / window_size
    sma = np.convolve(data, weights, mode='valid')
    return sma

N_SAMPLES = 128

# Open a serial connection to the device.

net_average = 0

x = bdaq.bdaq(0, 0, 250, 'COM13', 1)

for i in range(0,1):

    x.core.write_parameters_last(["HSADC_sample_count",
                                "HSADC_dual_channel_select",
                                "HSADC_start_acquisition"],
                                [N_SAMPLES, 0, 1])

    samples = []

    for i in range(0,N_SAMPLES):

        x.core.write_parameters_last(["HSADC_SAMPLE_channel",
                                    "HSADC_SAMPLE_index"],[0,i])
        
        current_sample = x.core.read_parameters(["HSADC_SAMPLE_value"])

        print("Sample [{_index}] = {_sample}".format( _index = i , _sample = current_sample ))

        samples.append(current_sample[0])

    print("Acquired samples: {_samples}".format(_samples = samples))
    print("Average of samples: {_average}".format( _average = sum(samples[10:])/len(samples[10:])))       

    _moving_average = simple_moving_average(samples,16)

    print("Moving average: {_average}".format( _average = sum(_moving_average)/len(_moving_average) ))

    net_average = net_average + sum(_moving_average)/len(_moving_average)

    plt.plot(samples)
    plt.show()

print(net_average/5)