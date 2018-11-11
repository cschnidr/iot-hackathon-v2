import json
import boto3
 
BUCKET_BASE     = 'insert-your-bucket-name-here'
TEMP_FILE       = '/tmp/temperatures.json'
MAX_READINGS    = int((60/5)*24) # one reading every 5 mins for 24 hours
MAX_READINGS    = MAX_READINGS - 1 # make it easy for calculations
 
def get_existing_values(device):
    s3 = boto3.resource('s3')
    existing_values = {"temperature_readings": [], "humidity_readings": [], "timestamps": []}
    try:
        s3.Bucket(BUCKET_BASE).download_file(device, TEMP_FILE)
        f = open(TEMP_FILE)
        existing_values = json.loads(f.read())
        f.close()
    except Exception as e:
        if e.response['Error']['Code'] == '404':
            print('No previous record for this device.')
        else:
            raise(e)
 
    return existing_values
 
def append_values_to_s3_object(device, existing_values, values_to_append):
    # Let's not store more than MAX_READINGS readings. Trim oldest if necessary.
    t_len = len(existing_values["temperature_readings"])
    if t_len > MAX_READINGS:
        print(t_len, MAX_READINGS, t_len-MAX_READINGS)
        existing_values["temperature_readings"] = existing_values["temperature_readings"][t_len-MAX_READINGS:]
 
    h_len = len(existing_values["humidity_readings"])
    if h_len > MAX_READINGS:
        existing_values["humidity_readings"] = existing_values["humidity_readings"][h_len-MAX_READINGS:]
 
    t_len = len(existing_values["timestamps"])
    if t_len > MAX_READINGS:
        existing_values["timestamps"] = existing_values["timestamps"][t_len-MAX_READINGS:]
 
 
 
    existing_values["temperature_readings"].append(values_to_append["temperature"])
    existing_values["humidity_readings"].append(values_to_append["humidity"])
    existing_values["timestamps"].append(values_to_append["timestamp"])
    print(existing_values)
    s3 = boto3.resource('s3')
    s3.Bucket(BUCKET_BASE).put_object(Body = json.dumps(existing_values), Key = device, ACL='public-read')
 
def lambda_handler(event, context):
    print('Event details:', event)
    device = event['device']
    existing_values = get_existing_values(device)
    print('Existing values:', existing_values)
    append_values_to_s3_object(device, existing_values, event)
