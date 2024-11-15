Features
Temperature and Humidity Monitoring: Uses a DHT11 sensor to measure and display real-time temperature and humidity levels.
Motion Detection: Detects movement using a PIR sensor and automates lighting accordingly.
Light Level Detection: Uses an LDR sensor to adjust lights based on ambient brightness.
Appliance Control: Manages lights and fans via relays based on environmental conditions and user input.
RFID Authentication: Ensures secure access with RFID-based user identification.
Bluetooth Control: Allows users to control lights and fans remotely using a Bluetooth module.
Data Logging: Saves temperature, humidity, motion, and light level data to an SD card every minute for analysis.
Event Logging: Tracks significant events like user access and environmental changes on the SD card.
LCD Display: Provides real-time data and system status on a 16x2 LCD.
Components Required
Hardware
Arduino Uno (or compatible)
DHT11 Sensor (Temperature and Humidity)
PIR Sensor (Motion Detection)
LDR Sensor (Light Intensity)
2-Channel Relay Module
RFID Module (MFRC522)
Bluetooth Module (HC-05/HC-06)
SD Card Module and SD Card
16x2 LCD Display with I2C Adapter
Connecting Wires and Breadboard
Power Supply (5V/9V)
Software
Arduino IDE
Required Libraries:
DHT
Wire
LiquidCrystal_I2C
SPI
MFRC522
SD
SoftwareSerial
Circuit Diagram
Overview:
DHT11: Connects to digital pin 2.
PIR Sensor: Connects to digital pin 7.
LDR Sensor: Connects to analog pin A0.
Relays: Connect to digital pins 8 and 12 for controlling lights and fans.
RFID Module: SPI connection using pins 10 (SS), 9 (RST), 11 (MOSI), 12 (MISO), 13 (SCK).
Bluetooth: Connects to pins 3 (RX) and 4 (TX) via SoftwareSerial.
LCD: Uses I2C, connected to SDA and SCL pins.
SD Card Module: Connects via SPI to pin 4 (CS).
Setup and Installation
Install Arduino IDE:

Download from Arduino's official site.
Install the required libraries via the Library Manager (Sketch > Include Library > Manage Libraries).
Assemble the Circuit:

Follow the circuit diagram to connect all components to the Arduino board.
Upload the Code:

Copy the provided code into the Arduino IDE.
Select the correct COM port and board type (Tools > Board).
Upload the code.
Power Up:

Provide power to the Arduino using a USB cable or external 9V adapter.
How It Works
Data Collection
The DHT11 sensor measures temperature and humidity.
The PIR sensor detects motion, while the LDR measures light intensity.
Appliance Control
Lights turn on automatically when motion is detected, and ambient light is low.
Fans activate based on a temperature threshold.
User Authentication
RFID cards authenticate users, logging access events on the SD card and displaying a confirmation message on the LCD.
Remote Control
Use a Bluetooth-capable device to send commands to turn appliances on or off manually.
Data Logging
Temperature, humidity, motion, and light data are logged every minute on the SD card for further analysis.
Command Reference for Bluetooth Control
Command	Action
1	Turn ON Light
0	Turn OFF Light
2	Turn ON Fan
3	Turn OFF Fan
Future Enhancements
Add WiFi integration for remote control via a web or mobile app.
Incorporate more sensors like gas, smoke, or sound for additional safety features.
Expand automation rules based on time schedules or user-defined conditions.
