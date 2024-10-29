# ESP8266 PlatformIO Project

This repository contains a PlatformIO project for an ESP8266 microcontroller. The project collects data and interacts with an API. This document will guide you through setting up the project, including the necessary prerequisites and first run.

## Prerequisites

Before starting, ensure you have the following installed on your machine:

### 1. [VS Code](https://code.visualstudio.com/)

- Download and install Visual Studio Code (VS Code), a powerful code editor with integrated tools for embedded development.

### 2. [PlatformIO Extension for VS Code](https://platformio.org/install/ide?install=vscode)

- Install the PlatformIO extension in VS Code. This will allow you to develop firmware for the ESP8266 directly in the editor.

### 3. [Git](https://git-scm.com/)

- Install Git, a version control system used to clone and manage this repository. You can download it [here](https://git-scm.com/).

Once installed, you can clone the repository using:

```bash
git clone <repository-url>
```

### 4. [Python 3.x](https://www.python.org/)

- Python is needed to process and plot data from the ESP8266.

### 5. Python Libraries

Install the following Python libraries, which are required to plot the data and make API requests:

- **numpy**
- **matplotlib**
- **python-dotenv**
- **requests**

You can install these using the Python package manager (pip). Open a terminal in VS Code and run:

```bash
pip install numpy matplotlib python-dotenv requests
```

## Project Setup

### Step 1: Clone the Repository

First, you need to clone this repository to your local machine. You can use Git for this or download the ZIP file from GitHub and extract it to a folder on your machine.

### Step 2: Open the Project in VS Code

1. Open **VS Code**.
2. In the **File** menu, choose **Open Folder**, and select the folder where the project is located.

PlatformIO should automatically recognize the `platformio.ini` file in the project root and configure the environment.

### Step 3: Copy and Modify Configuration File

Navigate to the `./include/` folder in the project directory and locate the `config_template.h` file.

1. **Copy the file** and **rename** the copy to `config.h`.
2. Open `config.h` in VS Code and replace the placeholder Wi-Fi credentials with your own:

   ```cpp
   const char* ssid = "your-SSID";
   const char* password = "your-PASSWORD";
   ```

### Step 4: Build and Upload the Firmware

With the project set up, it's time to upload the firmware to your ESP8266. Follow these steps in VS Code:

1. Plug your ESP8266 microcontroller into your computer via USB.
2. Open the **PlatformIO** sidebar in VS Code (click the alien icon in the sidebar).
3. Under **PROJECT TASKS**, expand your project name, and under **General**, click **Upload**. This will compile and upload the firmware to your ESP8266.

### Step 5: Monitor the Serial Output

Once the firmware is uploaded, you can monitor the output from the ESP8266 using VS Code:

1. In the **PlatformIO** sidebar, find **Monitor** under **PROJECT TASKS** and click it.
2. The ESP8266 will output an API URL with an IP address. Copy this IP address for the next step.

### Step 6: Create and Edit the `.env` File

Now, you need to create a `.env` file in the `./test/` directory.

1. In the **Explorer** sidebar of VS Code, navigate to the `./test/` folder.
2. Create a new file named `.env`.
3. Inside the `.env` file, add the following line:

   ```bash
   API_URL=http://<ip-address>/
   ```

   Replace `<ip-address>` with the IP address printed by the ESP8266 in the serial monitor.

### Step 7: Run the Python Script to Plot Data

With the `.env` file configured, you're ready to run the Python script to plot the data:

1. Open a terminal in VS Code (by clicking **Terminal > New Terminal** in the top menu).
2. Run the plotting script by typing:

   ```bash
   python ./test/plot.py
   ```

This script will fetch data from the ESP8266 using the API URL and plot the data using `matplotlib`.

## Troubleshooting

- **Serial Monitor Not Displaying**: Ensure the correct COM port is selected. PlatformIO should handle this automatically, but if not, check under **PROJECT TASKS > Platform > Ports** in the sidebar.
- **Wi-Fi Not Connecting**: Double-check your Wi-Fi SSID and password in the `config.h` file.
- **Python Errors**: Ensure all required Python libraries are installed correctly. You can install them using the command:

  ```bash
  pip install numpy matplotlib python-dotenv requests
  ```

## Conclusion

Once the steps above are completed, you should be able to successfully run the firmware on your ESP8266 and plot the data using Python. If you encounter any issues, feel free to reach out for help!
