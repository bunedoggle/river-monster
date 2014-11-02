#!/usr/bin/env python
#

import os
import re
import sys
import popen2
import serial 
import time

ser = serial.Serial('/dev/ttyUSB0', 115200)

while 1 :
    print ser.readline()

