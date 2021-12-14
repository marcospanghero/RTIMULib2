import sys, getopt

sys.path.append('.')
import RTIMU
import os.path
import time
import math

import ctypes

import pandas as pd
import io

import csv

import numpy as np

SETTINGS_FILE = "/home/pi/wasp-p16/platform/RTIMULib2/Linux/WASPDriver/python/RTIMULib"

## PROTOTYPES

def magnitude_acceleration(ax, ay, az):
    return math.sqrt(ax**2 + ay**2 + ax**2)

libc = ctypes.CDLL('libc.so.6')


print("Using settings file " + SETTINGS_FILE + ".ini")
if not os.path.exists(SETTINGS_FILE + ".ini"):
  print("Setting files needed - place RTIMULib.ini at the same path as the script")
  exit(1)

s = RTIMU.Settings(SETTINGS_FILE)
imu = RTIMU.RTIMU(s)

print("IMU Name: " + imu.IMUName())

if (not imu.IMUInit()):
    print("IMU Init Failed")
    sys.exit(1)
else:
    print("IMU Init Succeeded")

# this is a good time to set any fusion parameters

imu.setSlerpPower(0.2)
imu.setGyroEnable(True)
imu.setAccelEnable(True)
imu.setCompassEnable(True)

poll_interval = imu.IMUGetPollInterval()
print("Recommended Poll Interval: %dmS\n" % poll_interval)


csv_file = open("data-imu-extended.csv", mode="w")
data_writer = csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

data_writer.writerow(['Timestamp','ax','ay','ax','gx','gy','gz','mx','my','mz','fx','fy','fz','qposescal','qposex','qposey','qposez'])

input()
try:
    while True:
        start = time.clock()
        if imu.IMURead():
            
            data = imu.getIMUData()
            if data['accelValid']:
                data_writer.writerow([data['timestamp'], 
                data['accel'][0], data['accel'][1], data['accel'][2],
                data['gyro'][0], data['gyro'][1], data['gyro'][2],
                data['compass'][0], data['compass'][1], data['compass'][2],
                data['fusionPose'][0], data['fusionPose'][1], data['fusionPose'][2],
                data['fusionQPose'][0], data['fusionQPose'][1], data['fusionQPose'][2], data['fusionQPose'][3]]
                )
        end = time.clock() 
        libc.usleep(100000 - int((end-start)*1e6))


except KeyboardInterrupt:
    print("Exit and save data dump")
    csv_file.close()