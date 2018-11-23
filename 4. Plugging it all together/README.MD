# Create a new project in MOS Tool and modify/compile the new app
Beware the process for the Mac and Windows version of the MOS tool is intermixed below. The steps are the same but on the Mac version lots of it can be done in the GUI vs. CLI commands on the Windows version. However, you can also do CLI on your Mac. For Windows version go with the CLI commands.

1. Create a new app in MOS tool

MOS CLI --> make sure your are in the mos directory and not in another project dir. Use cd .. if necessary.
```
MOS CLI> mos clone https://github.com/cschnidr/esp8266-dht-aws
```
--> jump directly to step 5. if you used the CLI

**Step in the GUI:**

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-dhtapp-1.png" width="70%">



2. Choose a name for your app

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-dhtapp-2.png" width="70%">

3. Choose [mos.yml](https://github.com/cschnidr/iot-hackathon-v2/blob/master/src/mos.yml) in the dropdown and replace it with the provided one: 

![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-dhtapp-3.png "Modify mos.yml")

4. Do the same with the [main.c](https://github.com/cschnidr/iot-hackathon-v2/blob/master/src/fs/main.c) (Main program code)

![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-dhtapp-4.png "Modify main.c")

5. Compile and flash the new program (hit first wrench icon to build the firmware and then the flash button to flash it to the Wemos - see the picture above)

For CLI: Change into your project directory first
```
MOS CLI> cd esp8266-dht-aws
```
Build and Flash the app to your Wemos:
```
MOS CLI> mos build
MOS CLI> mos flash
```
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-mos-windows-1.PNG" width="90%">

# Connect your Wemos to Wireless
Change to the MOS tool in order to get your Wemos connected to a wireless network.

**Steps in the Mac GUI**

1. Click on "device setup" if your config windows below is not appearing

2. Connect to the serial port (restart MOS if the flashed app is recognized/appearing)

3. Configure your wireless --> device status should change to online
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-wifi-1.png" width="70%">

**Steps in CLI**

```
MOS CLI> mos wifi <SSID> <password>
```
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-mos-windows-2.PNG" width="90%">


# Setup MongooseOS to connect to AWS IoT Core

**Steps in the Mac GUI**

Go to MOS tool and click on "Device Config". On the Window titled "Provision device on AWS IoT" choose the region an policy as depicted below and hit "Provision with AWS IoT".
The MOS tool utilizes the already prepared AWS CLI and is automating the whole process (creating IoT shadow on AWS and setup everything with SSL certificated etc.).

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-awsiotsetup-1.png" width="90%">

**Steps in CLI**

```
MOS CLI> mos aws-iot-setup --aws-region eu-west-1 --aws-iot-policy mos-default
```
The MOS tool utilizes the already prepared AWS CLI and is automating the whole process (creating IoT shadow on AWS and setup everything with SSL certificated etc.).


# Testing Wemos connection to AWS IoT

In order to test if your device is sending data to AWS you can check the logs in the MOS tool:
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-checkinglog-1.png" width="90%">

To see if AWS is getting your data, you connect to aws.amazon.com and go to the "iot core" section:
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-testiot-1.png" width="90%">

Next you need to subscribe (click on test) to the MQTT channel (we use # in this example, which gives you all data your broker is receiving):
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-testiot-2.png" width="90%">

After a while (Wemos is reporting the temperature every 5min) you should see the following:
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-testiot-3.png" width="90%">


# Create the Lambda Function in AWS

Your Wemos is delivering data to AWS. The IoT service is obviously receiving that data. We now will put a rule in place, that this data will be sent to a Lambda function, which will format the data and store it in a single object/file in S3.
Lambda is a so-called serverless computing service running in AWS. You can run code to do something (like transforming and storing data) without worring about the required servers, operating systems and middlewares. AWS is managing it completely in the background. While you can run 1M requests in Lambda for free, the usage of it is charged only when running code (in 100ms increments and memory usage).
More on Lambda: https://aws.amazon.com/lambda/.

1. Go to your AWS Console
2. Go to the IoT Core Service, click on "act" and then on "create rule"
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-iotrule-1.png" width="60%">
3. Choose a name, a description and put the following SQL statement in it (it will filter all data delivered over MQTT)
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-iotrule-2.png" width="60%">

```
SELECT * FROM 'event/temp_humidity'
```

4. Add "invoke a lambda function" as the action (under set one or more actions)
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-iotrule-3.png" width="60%">
5. Click on "create a new lambda function" --> Lambda dashboard will be opened in a new tab
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-iotrule-4.png" width="60%">

6. Choose a name for your lambda function and choose "Python 3.6" as the runtime. Then choose create a custom role (to set permissions what your new lambda function can do) --> a new IAM tab opens.
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-lambda-1.png" width="60%">

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-lambda-3.png" width="60%">

7. Choose a name for the new role, edit the policy document with the json below:
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-role-1.png" width="60%">

```
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Effect": "Allow",
            "Action": "s3:*",
            "Resource": "*"
        },
        {
            "Effect": "Allow",
            "Action": [
                "logs:CreateLogGroup",
                "logs:CreateLogStream",
                "logs:PutLogEvents"
            ],
            "Resource": "arn:aws:logs:*:*:*"
        }
    ]
}
```

8. Click allow to create the new role and go back to the lambda dialog. Hit "create new function".

9. Paste the [Python code](https://github.com/cschnidr/iot-hackathon-v2/blob/master/aws%20/store_temp_in_s3.py) in the relevant window and choose File-Save in the code editor to complete your lambda function.
You have to adjust the code in order it writes in your S3 bucket that you created earlier.

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-lambda-2.png" width="60%">

10. Go back to the IoT Core dialog and choose your just created lambda function

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-lambda-5.png" width="60%">

11. After some minutes (next time your Wemos is transmitting data to AWS), the lambda function gets triggered the first time and should create a new file in the relevant S3 bucket. Go to the S3 dashboard to check for the file:
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-s3-1.png" width="60%">

12. Click on that file to see the URL (copy that URL for later use) to access it.

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-s3-2.png" width="60%">

13. Click on that file again and choose action-make public in order to make it publicly accessible

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-s3-3.png" width="60%">

14. Lastly you need to modify your [index.html](https://github.com/cschnidr/iot-hackathon-v2/blob/master/website/index.html), in order that the included javascript will access the the right data to visualize.
```
...
// insert the link to your JSON file in your S3 bucket below
 
        $.getJSON("https://s3-eu-west-1.amazonaws.com/wemos-s3/esp8266_EXAMPLE", function(data) {
...
```

15. Upload your index.html into your bucket and access it by a webbrowser
```
$ aws s3 cp index.html s3://wemos-s3/ --acl public-read
```

