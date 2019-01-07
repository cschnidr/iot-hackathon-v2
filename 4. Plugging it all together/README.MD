# Download, compile and flash a new app in MOS Tool

1. Download the source code

Make sure your are in the mos directory and not in another project dir. Use cd .. if necessary.
```
MOS CLI> mos clone https://github.com/cschnidr/esp8266-dht-aws
```

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-dhtapp-1.png" width="90%">

The source code will be downloaded from github and stored in the esp8266-dht-aws subfolder.

2. Compile and flash the new program 

Change into your project directory first
```
MOS CLI> cd esp8266-dht-aws
```
Build and Flash the app to your Wemos:
```
MOS CLI> mos build
MOS CLI> mos flash
```

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-mos-windows-1.PNG" width="90%">

# Connect your Wemos to a Wireless Network
Change to the MOS tool in order to get your Wemos connected to a wireless network.  
**Note:** This needs to be done everytime you flash your Wemos with a new app.

```
MOS CLI> mos wifi <SSID> <password>
```
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-mos-windows-2.PNG" width="90%">

Check the device log window to see if your Wemos is connected to the Wireless network.

# Setup MongooseOS to connect to AWS IoT Core

The MOS tool utilizes the already prepared AWS CLI and is automating the whole process to connect the Wemos with the IoT service of AWS (creating IoT shadow on AWS and setup everything with SSL certificated etc.).

```
MOS CLI> mos aws-iot-setup --aws-region eu-west-1 --aws-iot-policy mos-default
```

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-awsiotsetup-1.png" width="100%">


# Testing Wemos connection to AWS IoT

In order to test if your device is sending data to AWS you can check the logs in the MOS tool:
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-checkinglog-1.png" width="90%">

To see if AWS is getting your data, you connect to aws.amazon.com and go to the "iot core" section:

--> make sure you are in the region (see upper right corner) you used for the setup!!!
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-testiot-1.png" width="90%">

Next you need to subscribe (click on test) to the MQTT channel (we use # in this example, which gives you all data your broker is receiving):
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-testiot-2.png" width="90%">

After a while (Wemos is reporting the temperature every 5min) you should see the following:
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-testiot-3.png" width="90%">


# Create the Lambda Function in AWS

Your Wemos is delivering data to AWS. The IoT service is obviously receiving that data. We now will put a rule in place to send this data to a Lambda function, which will format the data and store it in a single object/file in S3.  
Lambda is a so-called serverless computing service running in AWS. You can run code to do something (like transforming and storing data) without worring about the required servers, operating systems and middlewares. AWS is managing it completely in the background. While you can run 1M requests in Lambda for free, the usage of it is charged only when running code (in 100ms increments and memory usage).

Check out this short video about serverless computing. It is another way (after VMs and containers) to consume compute resources.  
[![Introduction to AWS Lambda - Serverless Compute on Amazon Web Services](https://img.youtube.com/vi/eOBq__h4OJ4/0.jpg)](https://youtu.be/eOBq__h4OJ4)

1. Go to your AWS Console
2. Go to the IoT Core Service, click on "act" and then on "create rule"
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-iotrule-1.png" width="60%">
3. Choose a name, a description and put the following SQL statement in it (it will filter all data delivered over MQTT)
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-iotrule-2.png" width="60%">

```
SELECT * FROM 'event/temp_humidity'

```
**IMPORTANT:** Put in an enter after the select statement above. If not you get strange error messages that the IoT rule cannot be created.

4. Add "invoke a lambda function" as the action (under set one or more actions)
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-iotrule-3.png" width="70%">
5. Click on "create a new lambda function" --> Lambda dashboard will be opened in a new tab
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-iotrule-4.png" width="70%">

6. Choose a name for your lambda function and choose "Python 3.6" as the runtime. Then choose create a custom role (to set permissions what your new lambda function can do) --> a new IAM tab opens.
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-lambda-1.png" width="70%">

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-lambda-3.png" width="70%">

7. Choose a name for the new role, edit the policy document with the json (that describes which permissions will be assigned to the lambda function) below:
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-role-1.png" width="70%">

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

9. Paste the [Python code](https://raw.githubusercontent.com/cschnidr/iot-hackathon-v2/master/aws%20/store_temp_in_s3.py) in the relevant window and choose File-Save in the code editor to complete your lambda function.
You have to adjust the code in order it writes in your S3 bucket that you created earlier.

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-lambda-2.png" width="75%">

10. Go back to the IoT Core dialog and choose your just created lambda function

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-lambda-5.png" width="75%">

11. After some minutes (next time your Wemos is transmitting data to AWS), the lambda function gets triggered the first time and should create a new file in the relevant S3 bucket. Go to the S3 dashboard to check for the file:
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-s3-1.png" width="75%">

12. Click on that file to see the URL (copy that URL for later use) to access it.

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-s3-2.png" width="60%">

13. Click on that file again and choose action-make public in order to make it publicly accessible

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-s3-3.png" width="60%">


14. Download the [index.html](https://raw.githubusercontent.com/cschnidr/iot-hackathon-v2/master/website/index.html) to your machine. By web browser or CLI e.g. curl or wget.
```
curl -O https://raw.githubusercontent.com/cschnidr/iot-hackathon-v2/master/website/index.html
````

15. Adjust the index.html to use data from your bucket  
    To do so, check the content of your bucket in the AWS GUI and record the URL of the data file generated by your lambda function (e.g. https://s3-eu-west-1.amazonaws.com/yourbucketname/esp8266_YOURUNIQUEID)

    Edit the index.html to reflect the URL to your data file. A javascript (provided within the index.html) will read and visualize the data file directly in the browser.

The follwing lines need to be updated:
```
cat index.html | grep YOUR
    <link rel="shortcut icon" type="image/x-icon" href="https://s3-YOURREGION.amazonaws.com/YOURBUCKETNAME/favicon.ico"/> 
        var yourjsonpath = "https://s3-YOURREGION.amazonaws.com/YOURBUCKETNAME/esp8266_YOURUNIQUEID";
```

16. Copy the index.html to your bucket and make it publicly accessible
```
aws s3 cp index.html s3://yourbucketname/ --acl public-read
````

<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/index-edit-s3.gif" width="80%">

17. Find the public URL of your index.html and access it with a browser  
Usually something like: https://s3-eu-west-1.amazonaws.com/YOURBUCKETNAME/index.html

Congratulation - Enjoy your product :-) You might wanna adjust the lambda function to keep the date for a week or the c-code of the app to deliver the data in another frequency. Think of configuring the WIFI and AWS IoT again after your flashed the app to your wemos.  
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/4-final.png" width="80%">


