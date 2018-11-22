# Hardware Setup
Conntect the DHT11 (temperature and huminity) sensor to the Wemos. Make sure you connect the correct pins as depicted below. Otherwise you might destroy the DHT11 sensor!

DHT11
VCC = Power supply --> connect to 3V3 (3.3V) on your Wemos (next to pin D8)
DATA = Serial data output --> connect to pin D2 on your Wemos
GND/G = Ground --> connect to GND on your Wemos (next to pin D4)

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/2-hwsetup-1.jpg" width="50%">


# Start MOS Tool/IDE and connect your Board (Mac)
See below for Windows version!

Start the MOS tool by double clicking or CLI command. Browser starts up like below.
1. Choose the serial port, where Wemos it connected to. See first chapter if you don't know the serial port.
2. Choose ESP8266 with 4MB RAM
3. Choose the demo-c App

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/2-mongooseos-1.png" width="50%">

and click Flash do flash your Wemos with Mongoose OS and the demo-c app.

You see in the log section of the tool, that the application is downloaded from the web and flashed to your Wemos.

![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/2-mongooseos-2.png "Log while flashing")

The demo app is a blinking LED on the Wemos.

# Start MOS Tool/IDE and connect your Board (Windows)
Start the MOS tool by double clicking or CLI command. Browser starts up like below.
1. Choose the serial port, where Wemos it connected to. See first chapter if you don't know the serial port.
2. Choose ESP8266

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/2-mos-windows-1.PNG" width="80%">

From this point on you will use the CLI commands (in command input above) of the MOS tool!

3. Download the sources of the demo-c app
```
mos clone https://github.com/mongoose-os-apps/demo-c
```

4. Change to the app directory. You can click on the orange icon in the bottom-right corner to see your directory structure.
```
cd demo-c
```

5. Build and flash the demo-c app
```
mos build
mos flash
```

Your Wemos/ESP8266 is now running the sample app, which does blink the LED every second. Check out also the device log window.


# back to HOME
https://github.com/cschnidr/iot-hackathon-v2
