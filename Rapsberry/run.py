#!/usr/bin/env python
#

import os
import re
import sys
import popen2
import serial 
import time

input_fd_stdin = 0
input_fd_stdout = 0
input_fd_std_er = 0
raw_serial = 0

curr_sensor_id = ""
curr_sensor = {}

def configure_serial(device):
    CMD = "stty -F %s cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts" % (device)
    rc = os.system(CMD)
    print "configure_serial %s got %s" % (device, rc)
    time.sleep(3)

# ======================================================================

def do_open_serial():
    global raw_serial

    ## eco ## DEV_FILE = "/dev/ttyAMA0"
    # DEV_FILE = "/dev/ttyACM0"
    DEV_FILE = "/dev/ttyUSB0"

    # debug device
    ## DEV_FILE = "/dev/null"
    configure_serial(DEV_FILE)

    ## raw_serial = open(DEV_FILE, mode="w")
    raw_serial = serial.Serial(DEV_FILE, 115200)

# ======================================================================

def do_close_serial():
    raw_serial.close()

# ======================================================================

def check_line(line):
    # print "got: " + line.strip()

    ## EnO_sensor_0183193D sensor3: 113
    lineMatch = re.search("^(.+)\sEnO_sensor_([^\s]+)\s+(.+)$", line)
    if lineMatch:
        ts = lineMatch.group(1)
        sensorId = lineMatch.group(2)
        sensorData = lineMatch.group(3)
        # print ts, "matched sensor", sensorId, "data", sensorData
        check_sensor(ts, sensorId, sensorData)

# ======================================================================

def check_sensor(ts, sensorId, sensorData):
    global curr_sensor_id, curr_sensor

    sensorDataMatch = re.search("sensor(\d+): (.+)$", sensorData)

    if not sensorDataMatch:
        return  # done

    if curr_sensor_id != sensorId:
        # changed sensor id, clean values
        curr_sensor = {}
        curr_sensor_id = sensorId
        print "changing to sensor", sensorId

    sensor_key = sensorDataMatch.group(1)
    sensor_value = sensorDataMatch.group(2)
    curr_sensor[sensor_key] = sensor_value
    # print "curr_sensor dict: ", curr_sensor

    if ("1" in curr_sensor) and ("2" in curr_sensor) and ("3" in curr_sensor):
        do_send_data(ts, sensorId, curr_sensor["1"], curr_sensor["2"], curr_sensor["3"])
        # reset sensor id after sending
        curr_sensor_id = ""

# ======================================================================

def do_send_data(ts, sensor_id, sensor1_value, sensor2_value, sensor3_value):
    global raw_serial

    # cmdStr = "@STid:%s,sensor1:%s,sensor2:%s,sensor3:%s#" % (
    #    sensor_id, sensor1_value, sensor2_value, sensor3_value)

    locations = [ [42.65028, -71.30939], [42.65136,-71.31128] ]
    locationOffset = 1

    rawTemp = int(sensor3_value)
    convertedTemp = ((255 - rawTemp) * 40) / 255
    # print "rawTemp", rawTemp, "convertedTemp", convertedTemp

    ts2 = 123456

    cmdStr = "@SD%s,%s,%s,%s,%s,%s#\r\n" % (
        sensor_id, ts2, locations[locationOffset][0], locations[locationOffset][1], 
        convertedTemp, sensor1_value)

    print "sending %s" % cmdStr
    # raw_serial.write("@STthis is a test#")
    ## raw_serial.write(cmdStr)

    # cmdStr2 = "@SD1003,1234568,42.65028,-71.30939,15,1000\n\r"
    # raw_serial.write(cmdStr2)

    raw_serial.write("@GV#\r\n")
    print raw_serial.readlines()

    print "done sending"

# ======================================================================

def do_read_logs():
    CMD = "tail -F"
    INPUT_LOGS_DIR="/opt/fhem/log"
    LOG_FILES = "EnO_*.log"

    global input_fd_stdin, input_fd_stdout, input_fd_std_er
    
    (input_fd_stdin, input_fd_stdout, input_fd_std_err) = popen2.popen3(
        "%s %s/%s" % (CMD, INPUT_LOGS_DIR, LOG_FILES),
        mode='r')

    while True:
        line = input_fd_stdin.readline()
        if not line: break
        check_line(line.strip())

    input_fd_stdin.close()
    input_fd_stdout.close()
    input_fd_std_err.close()

# ======================================================================

if __name__ == "__main__":
    do_open_serial()
    do_read_logs()
    do_close_serial()
    sys.exit(0)
