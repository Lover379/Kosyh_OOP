import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy import stats

df = pd.read_csv('josephus_results.csv')

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))

ax1.plot(df['N'], df['Time_seconds'], 'o-')
ax1.set_xlabel('N')
ax1.set_ylabel('Time (seconds)')
ax1.set_title('Linear scale')
ax1.grid(True)

ax2.loglog(df['N'], df['Time_seconds'], 'o-')
ax2.set_xlabel('N')
ax2.set_ylabel('Time (seconds)')
ax2.set_title('Log-log scale')
ax2.grid(True)

log_N = np.log(df['N'])
log_T = np.log(df['Time_seconds'])
slope, intercept, r_value, p_value, std_err = stats.linregress(log_N, log_T)

N_fit = np.logspace(np.log10(min(df['N'])), np.log10(max(df['N'])), 100)
T_fit = np.exp(intercept) * (N_fit ** slope)
ax2.loglog(N_fit, T_fit, 'r--', label=f'O(n^{slope:.2f}), R²={r_value**2:.4f}')
ax2.legend()

plt.tight_layout()
plt.savefig('josephus_plot.png', dpi=150)
plt.show()

print(f"Complexity: O(n^{slope:.2f})")
print(f"R-squared: {r_value**2:.4f}")
print("\nResults:")
print(df.to_string(index=False))