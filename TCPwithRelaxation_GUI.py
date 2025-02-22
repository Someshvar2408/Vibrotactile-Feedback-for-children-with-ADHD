import socket
import tkinter as tk
from tkinter import ttk

ESP32_IP = "172.20.10.3"  
PORT = 1234  

client_socket = None  

def connect_to_esp32():
    global client_socket
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((ESP32_IP, PORT))
        print("Connected to ESP32!")
    except Exception as e:
        print(f"Failed to connect: {e}")

connect_to_esp32()  

def send_command(command):
    global client_socket
    try:
        if client_socket:
            client_socket.sendall((command + "\n").encode())
        else:
            print("No connection. Reconnecting...")
            connect_to_esp32()
            client_socket.sendall((command + "\n").encode())
    except (BrokenPipeError, ConnectionResetError):
        print("Connection lost. Reconnecting...")
        client_socket.close()
        connect_to_esp32()
        client_socket.sendall((command + "\n").encode())

def send_vibration():
    intensity = intensity_slider.get()
    duration = duration_slider.get()
    frequency = frequency_slider.get()
    send_command(f"CUSTOM {intensity} {duration} {frequency}")

def toggle_heartbeat():
    send_command("HEARTBEAT ON" if heartbeat_button["bg"] == "lightgray" else "HEARTBEAT OFF")
    heartbeat_button.config(bg="red" if heartbeat_button["bg"] == "lightgray" else "lightgray")

def toggle_relax():
    send_command("RELAX ON" if relax_button["bg"] == "lightgray" else "RELAX OFF")
    relax_button.config(bg="blue" if relax_button["bg"] == "lightgray" else "lightgray")

def stop_vibration():
    send_command("STOP")

# Create GUI window
root = tk.Tk()
root.title("Wireless Vibration Controller")

# Intensity Slider
ttk.Label(root, text="Intensity (0-255)").pack(anchor="center", pady=5)
intensity_slider = tk.Scale(root, from_=0, to=255, orient="horizontal")
intensity_slider.pack(anchor="center", pady=5)

# Duration Slider
ttk.Label(root, text="Duration (seconds)").pack(anchor="center", pady=5)  # Ensure label appears above slider
duration_slider = tk.Scale(root, from_=1, to=30, orient="horizontal")
duration_slider.pack(anchor="center", pady=5)

# Frequency Slider
ttk.Label(root, text="Frequency (Hz)").pack(anchor="center", pady=5)  # Ensure label appears above slider
frequency_slider = tk.Scale(root, from_=0, to=10, orient="horizontal")
frequency_slider.pack(anchor="center", pady=5)

# Buttons
tk.Button(root, text="Start Vibration", command=send_vibration).pack(pady=5)
heartbeat_button = tk.Button(root, text="Heartbeat Mode", command=toggle_heartbeat, bg="lightgray")
heartbeat_button.pack(pady=5)

relax_button = tk.Button(root, text="Relax Mode", command=toggle_relax, bg="lightgray")
relax_button.pack(pady=5)

tk.Button(root, text="Stop", command=stop_vibration).pack(pady=5)

# Run GUI
root.mainloop()
