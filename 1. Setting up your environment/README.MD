# Download Drivers and Connect your board via USB
**Windows10 seems to come with the appropriate USB-serial driver onboard. Just connect the board to your Windows10 computer and check the device manager for serial ports**

The board we're going to use is a WeMos D1 mini with an ESP8266. You can find all technical details about your board here: https://wiki.wemos.cc/products:d1:d1_mini . In order to make your board acessible from your System, you need to download the driver for you OS (https://wiki.wemos.cc/downloads). Go ahead and download and install the drivers on your system.

# Driver setup on OSX
1. Double click the "CH34x_Install_V1.4.pkg" to start the installation
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_1_install_driver_osx.png" width="70%">

2. Click "Continue"
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_2_install_driver_osx.png" width="70%">

3. Click "Continue"
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_3_install_driver_osx.png" width="70%">

4. Click "Install"
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_4_install_driver_osx.png" width="70%">

5. You need to restart your system twice in order to load the drivers and the system extension. For the first reboot click on "Restart".
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_5_install_driver_osx.png" width="70%">

6. After the reboot connect your board to your PC using a Micro USB cable. It will show up with a warning that OSX didn't allow the extenstion to be loaded. Go to "System Preferences" - "Security & Privacy" and click on "Allow".
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_6_install_driver_osx.png" width="70%">

7. Enable the extension from "jiangsu Qunheng Co., Ltd." an click "OK"
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_7_install_driver_osx.png" width="70%">

8. Enabling this extension requires your system to reboot again. Click "Restart" to reboot your system for the second time.
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_8_install_driver_osx.png" width="70%">

9. After the reboot open your Terminal App and enter the following command in order to verify that your WeMos board has been recognized.
```bash
ls /dev/tty* | grep serial
```
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_9_install_driver_osx.png" width="50%">
 
 
# Driver setup on Windows
Not required for Windows10. Just connect your board and check the device manager.

1. Double click the "CH341SER.exe" to start the driver installation

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_1_install_driver_win.png" width="50%">

<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_2_install_driver_win.png" width="50%">

2. Use the device manager to find your ESP8266 board in Windows:
<img src="https://github.com/cvolkmer/iot-hackathon/blob/master/images/1_3_install_driver_win.png" width="50%">

# Install MongooseOS command line tools

Check this page for details on how to install MongooseOS on your computer: https://mongoose-os.com/docs/quickstart/setup.md#1-download-and-install-mos-tool

Windows: Create C:\mos folder. Right-click this https://mongoose-os.com/downloads/mos-release/win/mos.exe, choose "Save link as", save mos.exe into the C:\mos folder. Double-click on mos.exe to start a Web UI. If it does not start, open command prompt, enter cd c:\mos and then mos --start-webview=false

Macs: First, install brew utility from here: https://brew.sh/
Then execute the following in CLI:
```
brew tap cesanta/mos
brew install mos
mos
```

# go back to Start page
https://github.com/cschnidr/iot-hackathon-v2
