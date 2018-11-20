# Setup IAM User for our IoT Project

The Mongoose OS Tool uses AWS CLI to setup AWS IoT service completely automatically. It creates resources in AWS including SSL certificates and prepares your Wemos with everything needed to talk to AWS.
In order to do so, we create a user in AWS with the required access policy. 

1. Connect to https://aws.amazon.com and login
2. Choose Ireland for the region to work
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-1.png" width="40%">
3. Go to IAM service
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-2.png" width="70%">
4. Create a new user
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-3.png" width="70%">
5. Choose a name and programmatic access only (API)
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-4.png" width="70%">
6. Attach IOT and S3 Policies as depicted
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-5.png" width="70%">
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-6.png" width="70%">
7. Download/copy the access key id and secret access key for your user (beware: this can be done once and only here)
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-7.png" width="70%">


# Setup AWS-CLI on your Computer

The AWS Command Line Interface (CLI) is a unified tool to manage your AWS services from CLI. https://aws.amazon.com/cli/

Easiest installation is:
For Windows
Download the [MSI-Installer-Package](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-windows.html#install-msi-on-windows) and run it

For Macs:
```
brew install awscli
```

In order to be able to use the AWS-CLI to configure AWS services and resources  IAM user credentials (downloaded above) and a region have to be configured.
```
$ aws configure
AWS Access Key ID [None]: AKIAIOSFODNN7EXAMPLE
AWS Secret Access Key [None]: wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY
Default region name [None]: eu-west-1
Default output format [None]: json
```

# Create a new S3 Bucket and put up the Webpage

1. Create a new S3 bucket by using CLI
```
aws s3 mb s3://yourbucketname
aws s3 ls
````

2. Download the [index.html](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/webpage/index.html) to your machine. By web browser or CLI e.g. curl or wget.
```
curl -O https://github.com/cschnidr/iot-hackathon-v2/blob/master/website/index.html
````

3. Adjust the index.html to use data from your bucket --> you maybe need to come back here later, when you know how the file with the iot-data (e.g. https://s3-eu-west-1.amazonaws.com/yourbucketname/esp8266_XXXXXX) is named.

4. Copy the index.html to your bucket and make it publicly accessible
```
aws s3 cp index.html s3://yourbucketname/ --acl public-read
````
5. Find the public URL of your index.html and access it with a browser

Go to the AWS interface (aws.amazon.com) into the S3 section
Choose the bucket you created to see the index.html in it.
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-s3-1.png" width="70%">

Click on the index.html to see the public URL to it
<img src="https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-s3-2.png" width="70%">






