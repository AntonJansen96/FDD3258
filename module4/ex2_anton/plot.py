#!/usr/bin/python3

import matplotlib.pyplot as plt
import loaddata as load

x = load.Col("shmoo.out", 1, 11, 91)
a = load.Col("shmoo.out", 2, 11, 91)
b = load.Col("shmoo.out", 2, 97, 177)
c = load.Col("shmoo.out", 2, 183, 263)

plt.figure()
plt.plot(x, a, label="host to device")
plt.plot(x, b, label="device to host")
plt.plot(x, c, label="device to device")
plt.xscale('log')
# plt.title("Nvidia RTX 2070 Super")
plt.xlabel("Transfer size (bytes)")
plt.ylabel("Bandwidth (GB/s)")
plt.legend()
# plt.show()
plt.savefig("plot2.pdf")
