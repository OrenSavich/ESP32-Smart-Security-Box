# Smart Security Box

## 🔐 Overview
The **Smart Security Box** is an IoT-based security system using an ESP32, the Blynk app, and multiple sensors. It monitors environmental conditions and provides real-time alerts based on detected changes. The system supports different alarm modes for various security levels.

🎥 **Demo Video**: [Watch here](https://youtu.be/JnvoE2-8a28)

## 🛠️ Features
- **Real-time Monitoring**: Displays temperature, humidity, and noise level data in the Blynk app.
- **Multiple Alarm Modes**: Ranging from passive monitoring to emergency alerts.
- **LED & Sound Alerts**: Visual and audible responses based on alarm levels.
- **Remote Control via Blynk**: Allows users to adjust security settings from anywhere.
- **Data Visualization**: Real-time values and trend analysis via gauge and chart widgets.

## 🎯 How It Works
1. **Data Collection**
   - **Temperature & Humidity Sensor**: Monitors environmental conditions.
   - **Microphone**: Detects noise levels and potential disturbances.
2. **Data Display in Blynk App**
   - **Temperature & Humidity**: Shown using gauge widgets.
   - **Noise Level**: Displayed via both gauge and chart widgets.
3. **Alarm Modes (Controlled via Blynk)**
   - **Do Nothing**: System is off.
   - **Suspicious Activity**: Low-level alert for potential disturbances.
   - **Definite Activity**: Higher alert level indicating notable movement.
   - **Emergency**: Triggers flashing police lights and a loud siren.

## 🔧 Hardware Requirements
- **ESP32**
- **DHT22 Sensor (Temperature & Humidity)**
- **Microphone Sensor**
- **Speaker**
- **LED Strip (Neopixel)**

## 📝 Circuit Connections
| Component         | Pin on ESP32 |
|------------------|-------------|
| DHT22 Sensor (Temperature & Humidity) | 16 |
| Microphone Module (Analog Input) | 34 |
| LED Strip (Neopixel) | 18 |
| Speaker | 26 |

## 🚀 Setup & Installation
1. **Install Arduino IDE** (if not already installed).
2. **Add Required Libraries**:
   - `Blynk`
   - `DHT sensor library`
3. **Upload the Code** to ESP32.
4. **Connect the Components** as per the table above.
5. **Configure the Blynk App**:
   - Add widgets for temperature, humidity, and noise level.
   - Add a selector widget for alarm modes.
6. **Power Up & Secure Your Space!**

## 📌 Authors
- **Oren Savich**
- **Rotem Peled**
