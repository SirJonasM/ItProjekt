import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import api_call

api_call.make_api_call()

# Read CSV into a pandas DataFrame
df = pd.read_csv('task8.csv')

# Convert the 'Buffer Length' column to string for the bar plots
df['Buffer Length'] = df['Buffer Length'].astype(str)

# Group by 'Mode' and 'Buffer Length', then calculate mean and standard deviation
grouped_df = df.groupby(['Mode', 'Buffer Length']).mean()
std_df = df.groupby(['Mode', 'Buffer Length']).std()

# Create a directory to save the plots
output_dir = 'plots/bar_plots'
os.makedirs(output_dir, exist_ok=True)

# Get unique buffer lengths
buffer_lengths = df['Buffer Length'].unique()

# Loop over each buffer length and create a separate plot
for buffer_length in buffer_lengths:
    # Filter the data for the current buffer length
    mean_df = grouped_df.xs(buffer_length, level='Buffer Length')
    std_current = std_df.xs(buffer_length, level='Buffer Length')
    
    # Plot the data
    modes = mean_df.index
    categories = mean_df.columns

    x = np.arange(len(categories))  # the label locations
    width = 0.16  # the width of the bars

    # Create subplots
    fig, ax = plt.subplots(figsize=(10, 6))

    # Loop through each mode and plot the bars
    for i, mode in enumerate(modes):
        ax.bar(x + i * width, mean_df.loc[mode], width, label=mode, yerr=std_current.loc[mode], capsize=5)

    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_ylabel('Time (ms)')
    ax.set_title(f'AES Encrypt/Decrypt Times by Mode (Buffer Size: {buffer_length}) with Standard Deviation')
    ax.set_xticks(x + width)
    ax.set_xticklabels(categories, rotation=45, ha='right')
    ax.legend()

    # Save the plot to a file instead of showing it
    filename = f"{output_dir}/aes_benchmark_{buffer_length}_buffer.png"
    plt.tight_layout()
    plt.savefig(filename)

    # Clear the figure to avoid overlap in future plots
    plt.clf()

print(f"All bar plots have been saved in '{output_dir}' directory.")
