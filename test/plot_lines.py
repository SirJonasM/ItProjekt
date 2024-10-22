import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import api_call

api_call.make_api_call()

# Read CSV into a pandas DataFrame
df = pd.read_csv('task8.csv')

# Convert the 'Buffer Length' column to string for the bar plots but keep it numeric for line graphs
df['Buffer Length'] = df['Buffer Length'].astype(int)

# Group by 'Mode' and 'Buffer Length', then calculate mean and standard deviation
grouped_df = df.groupby(['Mode', 'Buffer Length']).mean()
std_df = df.groupby(['Mode', 'Buffer Length']).std()

# Create a directory to save the plots
output_dir = 'plots/plot_lines'
os.makedirs(output_dir, exist_ok=True)

# Get unique modes
modes = df['Mode'].unique()

# Create the line graph with buffer length on the x-axis
buffer_lengths = sorted(df['Buffer Length'].unique())  # Sorted for the x-axis
categories = grouped_df.columns  # AES Encrypt/Decrypt categories

# Create subplots for each category (AES128 Encrypt, AES128 Decrypt, etc.)
for category in categories:
    plt.figure(figsize=(10, 6))

    # Plot each mode's line
    for mode in modes:
        # Extract data for the current mode and category
        mode_data = grouped_df.loc[mode][category]

        # Plot the data with buffer lengths on the x-axis and time on the y-axis
        plt.plot(buffer_lengths, mode_data, marker='o', label=mode)

    # Add titles and labels
    plt.title(f'Time vs Buffer Length for {category}')
    plt.xlabel('Buffer Length (Bytes)')
    plt.ylabel('Time (ms)')
    plt.xticks(buffer_lengths, rotation=45)
    plt.legend()

    # Save the plot to a file instead of showing it
    filename = f"{output_dir}/time_vs_buffer_{category.replace(' ', '_').lower()}.png"
    plt.tight_layout()
    plt.savefig(filename)

    # Clear the figure to avoid overlapping plots
    plt.clf()

print(f"Plots saved in '{output_dir}' directory.")
