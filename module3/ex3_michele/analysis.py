import numpy as np
import matplotlib.pyplot as plt

file_name = "pp_output.txt"

f_pp = open(file_name, 'r')

N = []
time = []

for line in f_pp :
    cols = line.split()
    N.append(int(cols[0]))
    time.append(float(cols[1]))

f_pp.close()

N = np.array(N)
time = np.array(time)

p = np.polyfit(N, time, deg=1)
time_fit = np.polyval(p, N)

print("Performance model parameters:")
print("latency   = p[1]   = s   = "+str(p[1])+" sec")
print("bandwidth = 1/p[0] = 1/r = "+str(1.0/p[0])+" B/sec")

plt.plot(N, time, 'r+', markersize=12.5, markeredgewidth=2.0, label='result')
plt.plot(N, time_fit, 'b--', linewidth=1.75, label='fit')
plt.title('Ping_pongfit', fontsize=25)
plt.ylabel('Time [sec]', fontsize=25)
plt.xlabel('Message size [B]', fontsize=25)
plt.xticks(fontsize=25)
plt.yticks(fontsize=25)
plt.show()
