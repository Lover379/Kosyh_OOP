import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('C++/Array/Array/josephus_results.csv')
df.columns = [c.strip() for c in df.columns]
x = df['N'].values
y = df['Time_seconds'].values

a = y[-1] / (x[-1]**2)

plt.figure(figsize=(14, 6))


plt.subplot(1, 2, 1)
plt.plot(x, y, 'r-o')
plt.title('Замеры')
plt.xlabel('N')
plt.ylabel('Время (сек)')
plt.grid(True, alpha=0.3)


plt.subplot(1, 2, 2)
x_pred = np.linspace(0, 1_500_000, 1000)
y_pred = a * (x_pred**2)
plt.plot(x_pred, y_pred, 'g--')
plt.plot(x, y, 'ro', markersize=4)
plt.title('Прогноз')
plt.xlabel('N')
plt.ylabel('Время (сек)')
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.show()