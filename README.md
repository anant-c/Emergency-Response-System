# Emergency Response System

This project aims to develop a dual-triggered emergency response system using the ESP8266 microcontroller for vehicles. The system can be activated manually through a push button 
or automatically through sensor data indicating an accident. Upon activation, the system sends an SOS email with the driver’s current GPS location to the authorities, ensuring prompt assistance. 
By integrating GPS, ultrasonic, vibration, and gyrosensors, the system provides a comprehensive solution for enhancing road safety and security in various emergency situations.
**This project aligns itself with The United Nations Software Development Goals (SDG) 11 i.e. "Sustainable cities and communities"** since improving emergency response mechanisms for drivers, 
can be inclusive, safe, resilient, and sustainable.

## Features

- Dual-triggered system.
- Send SOS with accurate GPS location to concerned authorities.
- Analyses data from multiple sensors including Ultrasonic sensor, Gyro sensor, Vibration sensor to detect accidents.
- Threshold based accident detection algorithm.

## Components used

- **ESP8266**:  Low-cost Wi-Fi microcontroller, with built-in TCP/IP networking software, and microcontroller capability.
  
<img src="https://github.com/anant-c/Emergency-Response-System/assets/88738817/be980873-1e6e-46e1-8ad1-abe452e3001b" height="200px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

- **MPU6050**:  MPU6050 sensor module is complete 6-axis Motion Tracking Device. It combines 3-axis Gyroscope, 3-axis Accelerometer and Digital Motion Processor all in small package. 
Also, it has additional feature of on-chip Temperature sensor. It has I2C bus interface to communicate with the microcontrollers.  

<img src="https://github.com/anant-c/Emergency-Response-System/assets/88738817/82d68208-a608-4c9e-a4d8-b0fdbd80803e" height="200px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

**HC-SR04**:  High-Conductance ultrasonic sensor, which consists of a transmitter and receiver. The sensor measures how far things are without touching them, and it uses sound waves to get the measurements right. Good for testing environment only!  

<img src="https://github.com/anant-c/Emergency-Response-System/assets/88738817/6dc6fbd5-d488-4c9c-bb95-fd40d1349506" height="200px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

**NEO-6M GPS**:  This module be used in applications requiring global positioning and navigation, like automotive vehicles, drones, pets, etc.  

<img src="https://github.com/anant-c/Emergency-Response-System/assets/88738817/5a35cf52-0ad4-4b50-881a-13c69c518ec6" height="200px">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

## Installation steps

1. - Fork the [repo](https://github.com/anant-c/Emergency-Response-System.git)
   - Clone the repo to your local machine `git clone https://github.com/anant-c/Emergency-Response-System.git`
   - Change current directory `cd cargo`
2. Install [Platform.io for VS Code](https://platformio.org/install/ide?install=vscode)

3. Make connections as the above circuit diagram.
   
4. Build the project.
   
5. Upload the code to the board.

6. Start the serial monitor to check output.

## References
- [Ultrasonic sensor](https://randomnerdtutorials.com/esp8266-nodemcu-hc-sr04-ultrasonic-arduino/)
- [GPS module](https://microcontrollerslab.com/neo-6m-gps-module-esp8266-nodemcu-track-location-google-maps/)
- [Gyro sensor](https://randomnerdtutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/)
