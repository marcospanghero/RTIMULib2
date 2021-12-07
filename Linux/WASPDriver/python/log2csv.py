import sys, getopt

sys.path.append('.')
import RTIMU
import os.path
import time
import math


import io
import numpy as np

SETTINGS_FILE = "/home/pi/wasp-p16/platform/RTIMULib2/Linux/WASPDriver/python/RTIMULib"

## PROTOTYPES

def magnitude_acceleration(ax, ay, az):
    return math.sqrt(ax**2 + ay**2 + ax**2)



position = np.array([0.0,0.0,0.0])
velocity = np.array([0.0,0.0,0.0])
static = False
threshold = 0.05




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

imu.setSlerpPower(0.0)
imu.setGyroEnable(True)
imu.setAccelEnable(True)
imu.setCompassEnable(True)

poll_interval = imu.IMUGetPollInterval()
print("Recommended Poll Interval: %dmS\n" % poll_interval)

f = open("data-imu.csv", "w", encoding="utf-8")

try:
    while True:
        if imu.IMURead():
            x, y, z = imu.getFusionData()
            print("%f %f %f" % (x,y,z))
            data = imu.getIMUData()
            fusionPose = data["fusionPose"]
            time.sleep(poll_interval*1.0/1000.0)


except KeyboardInterrupt:
    print("Exit and save data dump")
    f.close()