# serial         1   0.00281   3.83e-05  
# para_naive     32  0.000373  0.000149  
# para_critical  1   0.0148    9.36e-05  
# para_critical  2   0.0406    0.00461   
# para_critical  4   0.0615    0.00134   
# para_critical  8   0.0965    0.00222   
# para_critical  16  0.153     0.00655   
# para_critical  20  0.212     0.00643   
# para_critical  24  0.228     0.00627   
# para_critical  28  0.238     0.00617   
# para_critical  32  0.26      0.00399   
# para_shared    1   0.00521   1.52e-05  
# para_shared    2   0.00292   0.000113  
# para_shared    4   0.00157   0.000105  
# para_shared    8   0.000938  0.000101  
# para_shared    16  0.000653  8.7e-05   
# para_shared    20  0.00057   8.27e-05  
# para_shared    24  0.000515  7.95e-05  
# para_shared    28  0.000489  7.49e-05  
# para_shared    32  0.000464  7.85e-05  
# para_padded    1   0.0053    1.23e-05  
# para_padded    2   0.00296   0.000106  
# para_padded    4   0.00157   0.000107  
# para_padded    8   0.000967  0.000117  
# para_padded    16  0.000621  9.35e-05  
# para_padded    20  0.000571  8.43e-05  
# para_padded    24  0.000517  8.35e-05  
# para_padded    28  0.000462  8.09e-05  
# para_padded    32  0.000462  7.67e-05  

import matplotlib
from matplotlib import pyplot as plt

cores   = [1, 2, 4, 8, 16, 20, 24, 28, 32]

serialM = [0.00281]
serialS = [3.83e-05]

naiveM  = [0.000373]
naiveS  = [0.000149]

critM   = [0.0148, 0.0406, 0.0615, 0.0965, 0.153, 0.212, 0.228, 0.238, 0.26]
critS   = [9.36e-05, 0.00461, 0.00134, 0.00222, 0.00655, 0.00643, 0.00627, 0.00617, 0.00399]

sharedM = [0.00521, 0.00292, 0.00157, 0.000938, 0.000653, 0.00057, 0.000515, 0.000489, 0.000464]
sharedS = [1.52e-05, 0.000113, 0.000105, 0.000101, 8.7e-05, 8.27e-05, 7.95e-05, 7.49e-05, 7.85e-05]

paddedM = [0.0053, 0.00296, 0.00157, 0.000967, 0.000621, 0.000571, 0.000517, 0.000462, 0.000462]
paddedS = [1.23e-05, 0.000106, 0.000107, 0.000117, 9.35e-05, 8.43e-05, 8.35e-05, 8.09e-05, 7.67e-05]

plt.figure()

plt.plot([32], naiveS, label="naive = 3.73e-4 (s)", color='b')
plt.errorbar([32], naiveM, naiveS, marker="*", color='b')

plt.plot(cores, critM, label="critical", color='g')
plt.errorbar(cores, critM, critS, color='g')

plt.plot(cores, sharedM, label="shared", color="purple")
plt.errorbar(cores, sharedM, sharedS, color="purple")

plt.plot(cores, paddedM, label="padded", color="cyan")
plt.errorbar(cores, paddedM, paddedS, color="cyan")

plt.hlines(serialM[0], 0, 32, label="serial = 2.81e-3 (s)", color='r')

plt.yscale("log")
plt.axis([0, 33, 0, 0.27])
plt.xlabel("Cores")
plt.ylabel("Mean execution time (s)")
plt.grid(True)
plt.legend(loc=[0.5, 0.5])

plt.savefig("plot.pdf")
