#!/bin/python3

import matplotlib
from matplotlib import pyplot as plt

processes   = [8, 16, 32, 64, 128]
linear      = [4.794, 4.824, 4.365, 1.556, 3.741]
binary      = [7.415, 5.269, 4.527, 3.367, 3.663]
nonblocking = [4.850, 3.152, 2.011, 3.895, 1.224]
gather      = [5.044, 5.254, 5.542, 1.467, 3.638]
reduce      = [7.020, 5.164, 1.977, 3.907, 3.674]

plt.figure()
plt.plot(processes, linear, label="linear")
plt.plot(processes, binary, label="binary")
plt.plot(processes, nonblocking, label="non-blocking")
plt.plot(processes, gather, label="gather")
plt.plot(processes, reduce, label="reduce")

plt.axis([8, 128, 0, 8])

plt.xlabel("Number of processes")
plt.ylabel("Execution time (s)")

plt.legend()

plt.savefig("plot.pdf")
