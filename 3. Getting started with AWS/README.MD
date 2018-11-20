# Setup IAM User for our IoT Project

The Mongoose OS Tool uses AWS CLI to setup AWS IoT service completely automatically. It creates resources in AWS including SSL certificates and prepares your Wemos with everything needed to talk to AWS.
In order to do so, we create a user in AWS with the required access policy. 

1. Connect to https://aws.amazon.com and login
2. Choose Ireland for the region to work
![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-1.png "Choosing the AWS region")
3. Go to IAM service
![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-2.png "IAM user interface")
4. Create a new user
![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-3.png "Creating a new user")
5. Choose a name and programmatic access only (API)
![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-4.png "IAM user interface")
6. Attach IOT and S3 Policies as depicted
![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-5.png "Attaching IoT policy")
![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-6.png "Attaching S3 policy")
7. Download/copy the access key id and secret access key for your user (beware: this can be done once and only here)
![alt text](https://github.com/cschnidr/iot-hackathon-v2/blob/master/images/3-iamuser-7.png "IAM user interface")


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

# Create a new S3 Bucket


# Put up the Webpage in S3


# Create the Lambda Function in AWS




