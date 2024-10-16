import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import api_call

api_call.make_api_call()
# Read CSV into a pandas DataFrame
df = pd.read_csv('task8.csv')

# Set up the x-axis
modes = df['Mode']  # Group labels
index = np.arange(len(modes))  # The label locations
bar_width = 0.12  # Width of each bar

# Create subplots
fig, ax = plt.subplots()

# Plot each set of bars
ax.bar(index, df['AES128 Encrypt'], bar_width, label='AES128 Encrypt')
ax.bar(index + bar_width, df['AES128 Decrypt'], bar_width, label='AES128 Decrypt')
ax.bar(index + 2 * bar_width, df['AES192 Encrypt'], bar_width, label='AES192 Encrypt')
ax.bar(index + 3 * bar_width, df['AES192 Decrypt'], bar_width, label='AES192 Decrypt')
ax.bar(index + 4 * bar_width, df['AES256 Encrypt'], bar_width, label='AES256 Encrypt')
ax.bar(index + 5 * bar_width, df['AES256 Decrypt'], bar_width, label='AES256 Decrypt')

# Add labels, title, and legend
ax.set_xlabel('Mode')
ax.set_ylabel('Time (ms)')
ax.set_title('AES Performance by Mode')
ax.set_xticks(index + bar_width * 2.5)  # Position the labels correctly
ax.set_xticklabels(modes)
ax.legend()

# Show the plot
plt.show()
