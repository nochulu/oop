import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('results.csv')
df.columns = [c.strip() for c in df.columns]
x = df['N'].values
y = df['Calculation time (sec)'].values

a = y[-1] / (x[-1]**2)
x_pred = np.linspace(0, 2_000_000, 1000)
y_pred = a * (x_pred**2)

plt.figure(figsize=(10, 6))

plt.plot(x, y, 'r-o', label='Факт')
plt.plot(x_pred, y_pred, 'g--', label='Прогноз')

plt.title('Замеры и прогноз')
plt.xlabel('N')
plt.ylabel('Время (сек)')
plt.legend()
plt.grid(True, alpha=0.3)

plt.show()