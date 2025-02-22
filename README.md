# Vibrotactile-Feedback-for-children-with-ADHD
Created a vibrotactile feedback based wristband with ESP32C3 microcontroller and a Lilypad vibrator which can receive commands via a GUI wirelessly connected to the same WiFi
# Wireless Vibrotactile Feedback System

## 📌 Project Overview

This project implements a **wireless vibrotactile feedback system** using an **ESP32** microcontroller and a **Python GUI** over **TCP/IP communication**. It enables users to control vibration patterns remotely, making it useful for **assistive technology, ADHD management, and sensory feedback applications**.

## 🚀 Features

### 🔹 ESP32 Firmware

- **Custom Vibration Mode** – User-defined intensity, duration, and frequency.
- **Heartbeat Mode** – A realistic "lub-dub" heartbeat pattern with proper pauses.
- **Relaxation Mode** – A breathing-inspired vibration pattern to help reduce anxiety.
- **Auto-Reconnection** – ESP32 automatically reconnects to Wi-Fi and client if disconnected.

### 🔹 Python GUI

- **Wireless control** – Sends vibration commands over Wi-Fi to the ESP32.
- **Graphical Sliders** – Adjust **intensity, duration, and frequency** of custom vibrations.
- **Mode Selection** – Buttons to toggle **Heartbeat Mode, Relaxation Mode, and Stop vibration**.
- **Auto-Reconnection** – If disconnected, the GUI will automatically reconnect to the ESP32.

---

## 🛠️ Installation & Setup

### **1️⃣ Hardware Requirements**

- **ESP32** microcontroller
- **Vibration motor** (connected to ESP32 GPIO 2)
- **Laptop with Python 3 installed**
- **Wi-Fi connection (hotspot or router)**

### **2️⃣ ESP32 Setup**

1. **Flash the ESP32 firmware**:
   - Open `TCP_IP_withRelaxation.ino` in **Arduino IDE**.
   - Install required libraries (**WiFi.h**).
   - Enter **Wi-Fi SSID & Password** in the code.
   - Upload the sketch to ESP32.
2. **Get the ESP32's IP address** (printed in the Serial Monitor).

### **3️⃣ Python GUI Setup**

1. Install Python dependencies:
   ```bash
   pip install tkinter
   ```
2. Open `TCPwithRelaxation_GUI.py` and update **ESP32\_IP** with the ESP32's IP.
3. Run the GUI:
   ```bash
   python TCPwithRelaxation_GUI.py
   ```

---

## 🔄 How It Works

1. **ESP32 acts as a TCP server** and listens for commands.
2. **Python GUI (client) connects via Wi-Fi** and sends vibration commands.
3. ESP32 processes the command and activates the vibration motor accordingly.

---

## 🎮 Usage Guide

1. **Start the Python GUI** (`TCPwithRelaxation_GUI.py`).
2. **Set intensity, duration, and frequency** using sliders.
3. **Select a mode:**
   - `Start Vibration` – Triggers a **custom vibration**.
   - `Heartbeat Mode` – Activates a **realistic lub-dub heartbeat pattern**.
   - `Relax Mode` – Initiates **deep breathing-inspired vibration pulses**.
   - `Stop` – Turns off vibration.
4. **GUI auto-reconnects** if Wi-Fi drops.

---

## 🔧 Troubleshooting

### **ESP32 Not Connecting to Wi-Fi?**

- Ensure **correct Wi-Fi credentials** are in `TCP_IP_withRelaxation.ino`.
- Restart ESP32 and check the **Serial Monitor** for errors.

### **GUI Can't Connect to ESP32?**

- Verify that ESP32's **IP address is correctly entered** in `TCPwithRelaxation_GUI.py`.
- Run the following command to check if ESP32 is online:
  ```bash
  ping <ESP32_IP>
  ```
- Restart the ESP32 and the GUI.

### **Vibration Feels Too Fast or Slow?**

- Adjust **intensity, duration, and frequency sliders** in the GUI.
- Modify **timing values** in `handleVibration()` in ESP32 code.

---

## 📌 Future Improvements

- ✅ Add **MQTT support** for remote control over the Internet.
- ✅ Implement **haptic feedback profiles** for different user needs.
- ✅ Create a **mobile app** to control the ESP32 directly.

---

## 🏆 Credits

Developed by **Someshvar** 🔥

If you find this project useful, give it a ⭐ on **GitHub**!

Happy Hacking! 🚀😎

