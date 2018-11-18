# Setup IAM User for our IoT Project

The Mongoose OS Tool uses AWS CLI to setup AWS IoT service completely automatically. It creates resources in AWS including SSL certificates and prepares your Wemos with everything needed to talk to AWS.
In order to do so, we create a user in AWS with the required access policy. 

1. Connect to https://aws.amazon.com and login
2. Go to IAM service
3. Create a new user


# Setup AWS-CLI on your Computer

The AWS Command Line Interface (CLI) is a unified tool to manage your AWS services from CLI. https://aws.amazon.com/cli/

Easiest installation is:
For Windows
Download the [MSI-Installer-Package](https://docs.aws.amazon.com/cli/latest/userguide/awscli-install-windows.html#install-msi-on-windows) and run it

For Macs:
```
brew install awscli
```

In order to be able to use the AWS-CLI to configure AWS services and resources  IAM user credentials and a region have to be configured.
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




