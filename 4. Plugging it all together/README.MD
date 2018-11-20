# Create a new project in MOS Tool and modify/compile the new app

1. Create a new app in MOS tool

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-dhtapp-1.png" width="70%">

2. Choose a name for your app

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-dhtapp-2.png" width="70%">

3. Choose mos.yml and replace it with the provided one: 

![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-dhtapp-3.png "Modify mos.yml")

4. Do the same with the main.c (Main program code)

![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-dhtapp-4.png "Modify main.c")

5. Compile and flash the new program (hit first wrench icon to build the firmware and then the flash button to flash it to the Wemos)


# Connect your Wemos to Wireless
Change to the MOS tool in order to get your Wemos connected to a wireless network.

1. Click on "device setup" if your config windows below is not appearing

2. Connect to the serial port (restart MOS if the flashed app is recognized/appearing)

3. Configure your wireless --> device status should change to online
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-wifi-1.png" width="70%">


# Setup MongooseOS to connect to AWS IoT Core

Go to MOS tool and click on "Device Config". On the Window titled "Provision device on AWS IoT" choose the region an policy as depicted below and hit "Provision with AWS IoT".
The MOS tool utilizes the already prepared AWS CLI and is automating the whole process (creating IoT shadow on AWS and setup everything with SSL certificated etc.).

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-awsiotsetup-1.png" width="70%">


# Testing Wemos connection to AWS IoT



# Create the Lambda Function in AWS




