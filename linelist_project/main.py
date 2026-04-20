import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter

df = pd.read_csv('results.csv')
df.columns = [c.strip() for c in df.columns]

x = df['N'].values
y = df['Time(sec)'].values

plt.style.use('seaborn-v0_8-muted')
plt.figure(figsize=(10, 6), dpi=100)

plt.plot(x, y, color='#d62728', marker='o', markersize=4, linestyle='-', linewidth=1.5, label='Actual Time')

plt.title('Зависимость времени выполнения от N', fontsize=14, pad=15)
plt.xlabel('Количество элементов (N)', fontsize=12)
plt.ylabel('Время (секунды)', fontsize=12)

ax = plt.gca()
formatter = ScalarFormatter(useMathText=True)
formatter.set_scientific(True)
formatter.set_powerlimits((-1, 1))
ax.xaxis.set_major_formatter(formatter)

plt.grid(True, which='major', linestyle='--', alpha=0.7)
plt.grid(True, which='minor', linestyle=':', alpha=0.4)
plt.minorticks_on()

plt.legend()
plt.tight_layout()

plt.show()