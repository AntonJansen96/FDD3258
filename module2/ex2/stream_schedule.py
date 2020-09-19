import numpy as np
import matplotlib.pyplot as plt

schedules = ['static', 'dynamic', 'guided']

bandwidth = np.array(   [[24717.8, 25285.0, 24779.9, 25445.1, 24729.7, 25078.1, 25098.7, 25125.9, 24638.9, 24438.8],    # static
                         [461.3,   475.5,   503.1,   460.4,   469.0,   474.7,   461.6,   473.6,   470.4,   476.8  ],    # dynamic
                         [25707.3, 25952.8, 25898.8, 25752.7, 25906.8, 25661.1, 25798.2, 25773.4, 25819.0, 25979.0]])   # guided

bandwidth_avg = np.mean(bandwidth, axis=1)
bandwidth_std = np.std(bandwidth, axis=1)
print(schedules)
print(bandwidth_avg)
print(bandwidth_std)

fig, ax = plt.subplots()
ax.bar(np.arange(len(schedules)), bandwidth_avg,
       yerr=bandwidth_std,
       align='center',
       alpha=0.5,
       ecolor='black',
       capsize=15)
ax.set_xticks(np.arange(len(schedules)))
ax.set_xticklabels(schedules, fontsize=20.0)
ax.yaxis.set_tick_params(labelsize=20.0)
ax.set_title('STREAM copy kernel schedule bandwith test', fontsize=20.0)
ax.yaxis.grid(True)
plt.show()
