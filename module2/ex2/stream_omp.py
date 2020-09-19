import numpy as np
import matplotlib.pyplot as plt

n_threads = np.array([1, 2, 4, 8, 12, 16, 20, 24, 28, 32])

bandwidth = np.array(   [[6352.5, 6314.3,  6484.3,  6422.8,  6433.2 ],  # 1
                        [12130.6, 12477.5, 12161.8, 12316.0, 12294.6],  # 2
                        [22154.7, 22035.4, 23074.9, 23266.1, 22184.7],  # 4
                        [27313.3, 23959.8, 26670.7, 27341.2, 26238.0],  # 8
                        [25752.7, 25702.4, 25707.3, 25807.1, 25914.8],  # 12
                        [26177.6, 26177.6, 26185.8, 26152.1, 26169.4],  # 16
                        [26037.4, 25931.8, 26041.5, 26020.3, 26142.9],  # 20
                        [25835.9, 25914.8, 25906.8, 25897.8, 26143.9],  # 24
                        [25835.9, 25860.8, 25576.0, 25847.9, 25996.1],  # 28
                        [25823.0, 25744.8, 25690.6, 25715.2, 25798.2]]  # 32
                    )

bandwidth_avg = np.mean(bandwidth, axis=1)
bandwidth_std = np.std(bandwidth, axis=1)
print(n_threads)
print(bandwidth_avg)
print(bandwidth_std)

plt.errorbar(n_threads, bandwidth_avg, bandwidth_std, fmt='ko--', linewidth=1.25, markersize=7.5, markeredgewidth=1.75, capsize=7.5, ecolor='r')
plt.title('STREAM copy kernel multithred bandwith test', fontsize=20.0)
plt.xlabel('# threads', fontsize=20.0)
plt.ylabel('MB/s', fontsize=20.0)
plt.xticks(fontsize=20.0)
plt.yticks(fontsize=20.0)
plt.show()
