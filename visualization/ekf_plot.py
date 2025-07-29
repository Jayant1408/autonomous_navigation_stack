import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("../localization/ekf_log.csv")

plt.figure(figsize=(10,6))
plt.plot(df['x_est'], df['y_est'], label='EKF Estimate', linewidth=2)
plt.scatter(df['x_meas'], df['y_meas'], color='red', alpha=0.6, s=20, label='Noisy Measurements')
plt.title("EKF Localization: Estimated vs Measured Trajectory")
plt.xlabel("X Position (m)")
plt.ylabel("Y Position (m)")
plt.legend()
plt.grid()
plt.savefig("ekf_trajectory.png")
plt.show()
