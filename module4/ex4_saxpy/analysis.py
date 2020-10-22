import numpy as np
import matplotlib.pyplot as plt

size =  np.array([10000, 50000, 100000, 500000, 1000000])
time_cpu = np.array([0.000052, 0.000254, 0.000508, 0.002454, 0.004724], dtype=float)*1e3
time_gpu =  np.array([0.001354, 0.001484, 0.001744, 0.001776, 0.002581], dtype=float)*1e3

plt.semilogx(size, time_cpu, 'rx--', linewidth=1.75, markersize=12.5, label='CPU')
plt.semilogx(size, time_gpu, 'bo--', linewidth=1.75, markersize=7.5, label='GPU')
plt.xticks(fontsize=30.0)
plt.yticks(fontsize=30.0)
plt.title('SAXPY: CPU vs GPU', fontsize=30.0)
plt.xlabel('Array size', fontsize=25.0)
plt.ylabel('Time [ms]', fontsize=25.0)
plt.legend(fontsize=20.0)
plt.show()
