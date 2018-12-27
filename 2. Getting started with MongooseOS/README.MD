# Hardware Setup
Conntect the DHT11 (temperature and huminity) sensor to the Wemos. Make sure you connect the correct pins as depicted below. Otherwise you might destroy the DHT11 sensor!

**Wiring DHT11 and Wemos**

VCC = Power supply --> connect to **3V3** (3.3V) on your Wemos (next to pin D8)

DATA = Serial data output --> connect to pin **D2** on your Wemos

GND/G = Ground --> connect to **GND/G** on your Wemos (next to pin D4)

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/2-hwsetup-1.jpg" width="50%">


# Start MOS Tool/IDE and connect your Board

Start the MOS tool by double clicking (Windows) or CLI (Mac) command. Browser starts up like below.

```
mos
```

1. Choose the serial port, where Wemos it connected to. See first chapter if you don't know the serial port.
2. Choose ESP8266

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/2-mos-windows-1.PNG" width="80%">

From this point on you will use the CLI commands (in command input above) of the MOS tool.

3. Download the sources of the demo-c app
We will download, compile and install a demo app in order to test the setup.
```
mos clone https://github.com/mongoose-os-apps/demo-c
```

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/2-mos-cli-1.PNG" width="80%">

4. Change to the app directory. You can click on the orange icon in the bottom-right corner to see your directory structure.
```
cd demo-c
```

5. Build and flash the demo-c app
```
mos build
mos flash
```

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/2-mos-cli-2.PNG" width="80%">

Your Wemos/ESP8266 is now running the sample app, which does blink the LED every second. Check out also the device log window.


# back to HOME
https://github.com/cschnidr/iot-hackathon-v2
