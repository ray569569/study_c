import numpy as np
import matplotlib.pyplot as plt
time = np.linspace(0.5, 1, 100)
def vout(t): return np.exp(-(t-0.5)/0.05)
plt.plot(time, vout(time), label='Vout')
plt.xlabel('Time(ms)')
plt.ylabel('Voltage(V)')
plt.legend()
plt.show()
