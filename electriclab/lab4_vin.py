import numpy as np
import matplotlib.pyplot as plt
time = np.linspace(0, 20*10**-6, 100)
def vout(t): return np.exp(-(t)*(10**6))
plt.plot(time, vout(time), label='Vout')
plt.xlabel('Time (s)')
plt.ylabel('Voltage (V)')
plt.legend()
plt.show()
