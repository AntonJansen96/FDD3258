import numpy as np
import matplotlib.pyplot as plt

file_name = "pp_output_out_of_n.txt"
# file_name = "pp_output_on_node.txt"
print(file_name)

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
print("latency   = p[1]   = s   = "+str(p[1]*1e3)+" ms")
print("bandwidth = 1/p[0] = 1/r = "+str((1.0/p[0])*1e-9)+" GB/s")

plt.plot(N*1e-9, time*1e3, 'r+', markersize=15.0, markeredgewidth=2.0, label='result')
plt.plot(N*1e-9, time_fit*1e3, 'b--', linewidth=2.25, label='fit')
plt.title('Ping-pong linear fit', fontsize=30)
plt.ylabel('Time [ms]', fontsize=30)
plt.xlabel('Message size [GB]', fontsize=30)
plt.xticks(fontsize=30)
plt.yticks(fontsize=30)
plt.legend(fontsize=20)
plt.xlim([N[0]*1e-9,N[-1]*1e-9])
plt.show()

# Intercept as N->0

s = []
for K in range(1,len(time)) :
    ps = np.polyfit(N[0:K], time[0:K], deg=1)
    s.append(ps[1])

s = np.array(s)
K = np.array(range(1,len(time)))

"""
M = 15
s_hat = np.mean(s[0:M])*1e3
"""
# Conservative estimate: just take the maximum
s_hat = np.max(s)*1e3

print("Cumulative latency estimate :")
print("s_hat = "+str(s_hat)+" ms")

plt.plot(K, s*1e3, 'k.-', markersize=12.5, markeredgewidth=1.5, linewidth=1.5)
# plt.plot(K[0:M], s_hat*np.ones(M), 'r--',  linewidth=1.75)
plt.title('Latency', fontsize=30)
plt.ylabel('s [ms]', fontsize=30)
plt.xlabel('#points', fontsize=30)
plt.xlim([K[0],K[-1]])
plt.xticks(fontsize=30)
plt.yticks(fontsize=30)
plt.show()


