import numpy as np
import matplotlib.pyplot as plt

n_threads = np.array([1, 2, 4, 8, 12, 16, 20, 24, 28, 32])

# n=64 (hyperthreading)
t_64_threads = np.array([2.799519, 2.787354, 2.734193, 2.732953, 2.792026, 2.755549, 2.735955, 2.743173, 2.768430, 2.769972])

t_threads = np.array(   [[7.255416, 7.302536, 7.283108, 7.275580, 7.262914],
                         [3.675594, 3.687958, 3.683801, 3.681303, 3.702894],
                         [1.891688, 1.926816, 1.940373, 1.926323, 1.912227],
                         [1.082925, 1.078334, 1.058655, 1.054971, 1.044679],
                         [1.053012, 1.025971, 1.048728, 1.025225, 1.026796],
                         [0.953984, 0.839374, 0.864454, 0.849564, 0.937850],
                         [1.649243, 1.645614, 1.644093, 1.641439, 1.644627],
                         [1.707667, 1.691395, 1.684206, 1.699948, 1.681377],
                         [1.748004, 1.755520, 1.754891, 1.766710, 1.792197],
                         [1.867718, 1.855628, 1.846609, 1.884213, 1.841750]])

t_serial = np.array([4.642212, 4.688698, 4.744317, 4.659971, 4.630258])

print("Execution time 64 threads = "+str(np.mean(t_64_threads))+"+/"+str(np.std(t_64_threads))+" sec")

print("n_threads = ")
print(n_threads)

t_mean = np.mean(t_threads, axis=1)

print("t_min =")
print(t_mean)

t_std = np.std(t_threads, axis=1)

print("t_sdt =")
print(t_std)

t_serial_mean = np.mean(t_serial)

print("Mean execution time serial = "+str(t_serial_mean))

plt.plot([0,34], [t_serial_mean, t_serial_mean], 'b-', linewidth=1.75, label='Serial')
plt.errorbar(n_threads, t_mean, t_std, fmt='kx--', linewidth=2.5, markersize=20.0, markeredgewidth=2.5, capsize=15.0, ecolor='r', label='OpenMP')
plt.title('DTFW speedup test', fontsize=30.0)
plt.legend(fontsize=30.0)
plt.xlabel('# threads', fontsize=30.0)
plt.xlim([0,34])
plt.ylabel('Time [s]', fontsize=30.0)
plt.xticks(fontsize=30.0)
plt.yticks(fontsize=30.0)
plt.show()

