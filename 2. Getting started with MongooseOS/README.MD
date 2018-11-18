# Hardware Setup
Conntect the DHT11 (temperature and huminity) sensor to the Wemos. Make sure you connect the correct pins as depicted below. Otherwise you might destroy the DHT11 sensor!

DHT11
VCC = Power supply --> connect to 3V3 (3.3V) on your Wemos (next to pin D8)
DATA = Serial data output --> connect to pin D2 on your Wemos
GND/G = Ground --> connect to GND on your Wemos (next to pin D4)

![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/2-hwsetup-1.jpg "Connecting DHT11 to Wemos")


# Start MOS Tool/IDE and connect your Board
Start the MOS tool by double clicking or CLI command. Browser starts up like below.
1. Choose the serial port, where Wemos it connected to. See first chapter if you don't know the serial port.
2. Choose ESP8266 with 4MB RAM
3. Choose the demo-c App

![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/2-mongooseos-1.jpg "Connecting to the board")

and click Flash do flash your Wemos with Mongoose OS and the demo-c app.

You see in the log section of the tool, that the application is downloaded from the web and flashed to your Wemos.

![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/2-mongooseos-2.jpg "Log while flashing")

The demo app is a blinking LED on the Wemos.


# Troubleshooting
