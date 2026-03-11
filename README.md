# Smart Adaptive Streetlight System (ESP32)

An IoT-based smart streetlight prototype that dynamically adjusts brightness based on ambient light, motion detection, and real-time clock synchronization.

## Overview

Traditional streetlights remain at full brightness all night, wasting energy.  
This project introduces an **ESP32-based adaptive streetlight system** that optimizes power usage using:

- Ambient Light Detection (LDR)
- Motion Detection (PIR)
- Time-based Power Saving Mode
- PWM Brightness Control
- NTP Time Synchronization

The system automatically reduces brightness late at night and boosts it when motion is detected.

---

## Hardware Components

| Component | Purpose |
|--------|--------|
| ESP32 | Main microcontroller |
| PIR Sensor | Motion detection |
| LDR Sensor Module | Ambient light sensing |
| LED + Resistor | Streetlight simulation |
| Breadboard | Prototyping |
| Jumper Wires | Connections |

---

## Circuit Diagram

https://github.com/Ayancoder1/Smart-Adaptive-Streetlight-System/blob/main/Circuit%20Diagram.png

### ESP32 Connections

| ESP32 Pin | Component |
|----------|-----------|
| GPIO12 | PIR Output |
| GPIO32 | LDR Analog Output |
| GPIO14 | LED (PWM Output) |
| 3.3V | Sensors VCC |
| GND | Common Ground |

---

## Working Principle

The system works in **three main phases**.

### 1️⃣ Ambient Light Control
The LDR measures ambient light intensity.

- Daytime → LED OFF
- Evening → LED brightness gradually increases
- Night → Full brightness

### 2️⃣ Time-Based Power Saving Mode
Using **NTP time synchronization**, the system identifies late-night hours.

Time Window: 10:30 PM – 5:30 AM


During this time:
- LED runs at **60% brightness** to save energy.

### 3️⃣ Motion Trigger Boost
If motion is detected during the power-saving period:

- PIR triggers
- Brightness increases to **100%**
- Returns to **60%** when motion stops

---

## Features

- Adaptive brightness control
- Energy-efficient street lighting
- Motion-triggered safety lighting
- Automatic time synchronization
- Periodic system logging

---

## Software

Developed using:

- Arduino IDE
- ESP32 WiFi Library
- NTP Time Library

---

## Source Code

The complete source code is available in: https://github.com/Ayancoder1/Smart-Adaptive-Streetlight-System/blob/main/Smart_streetlight_Project.ino

---

## Serial Monitor Logging

The system logs its status every **30 minutes** including:

- Current Time
- LDR Value
- PIR Status
- LED Brightness Level

---

## Future Improvements

Possible upgrades include:

- LoRa based streetlight mesh network
- IoT dashboard using Thingspeak or Blynk
- Real-time fault detection
- Smart city integration
- Remote monitoring system

---

## Documentation

Full project report available here: https://github.com/Ayancoder1/Smart-Adaptive-Streetlight-System/blob/main/Ayan%20Kar%20OSHW%202026%20Project%20Report.pdf


---

## Author

**Ayan Kar**  
B.Tech Electrical Engineering  
Narula Institute of Technology  

---

## License

This project is open-source under the MIT License.
