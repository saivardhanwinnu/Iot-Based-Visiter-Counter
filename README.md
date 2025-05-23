# 👥 Visitor Counter using ESP8266

This project is a simple visitor counter system built using the ESP8266 microcontroller and IR sensors. It counts the number of people entering and exiting a room or space and can display the count on a serial monitor or web interface.

## 🚀 Features

- Count visitors entering and exiting a room
- Reset count via code or button
- Works offline or can send data to IoT platforms (optional)
- Powered by ESP8266 (e.g., NodeMCU or WeMos D1 Mini)

## 🛠️ Components Used

- ESP8266 Board (e.g., NodeMCU)
- 2x IR Sensors (entry and exit)
- Jumper Wires
- Breadboard or PCB
- Optional: OLED Display or Web Dashboard

## 🧑‍💻 How It Works

- IR sensors detect motion at the entrance and exit
- Logic in the code determines direction of movement
- Counter is incremented or decremented based on direction
- Data is shown via serial monitor or optionally on a web interface

## 🔌 Circuit Diagram

📌 (Add an image or Fritzing diagram here if available)

## 🖥️ Programming

- Code written in Arduino (.ino) format
- Developed using the Arduino IDE
- Upload the `.ino` file to your ESP8266 board

## 📦 Getting Started

1. Clone this repo
2. Open `.ino` file in Arduino IDE
3. Connect your ESP8266 board
4. Select correct Board and Port from **Tools** menu
5. Upload the code

```bash
git clone https://github.com/yourusername/visitor-counter-esp8266.git
