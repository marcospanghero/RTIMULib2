import sys, getopt

sys.path.append('.')
import RTIMU
import os.path
import time
import math

from scipy.signal import butter, sosfiltfilt, sosfreqz
from scipy.spatial.transform import Rotation as R
import collections 

import io

import transformations as tft

import numpy as np

SETTINGS_FILE = "/home/pi/wasp-p16/platform/RTIMULib2/Linux/WASPDriver/python/RTIMULib"

## PROTOTYPES

def magnitude_acceleration(ax, ay, az):
    return math.sqrt(ax**2 + ay**2 + ax**2)


def butter_bandpass(lowcut, highcut, fs, order=5):
        nyq = 0.5 * fs
        low = lowcut / nyq
        high = highcut / nyq
        sos = butter(order, [low, high], analog=False, btype='band', output='sos')
        return sos

## VARIABLES
buffer_len = 11
buffer_ax = collections.deque(maxlen=buffer_len)
buffer_ay = collections.deque(maxlen=buffer_len)
buffer_az = collections.deque(maxlen=buffer_len)

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

# Setup bandpass filter
fs = 1.0/(poll_interval*1e-3)
lowcut = 5.0
highcut = 40.0
order=1

bandpass = butter_bandpass(lowcut, highcut, fs, order=order)

if imu.IMURead():
    timestamp_p = imu.getIMUData()["timestamp"] 
    accelerations_p = np.array(imu.getIMUData()["accel"])
    velocities_p = np.array([0,0,0])
    position_p = np.array([0,0,0])
else:
    print("Failed to read once")
    sys.exit(1)

f = open("data-imu.csv", "w", encoding="utf-8")


#read first timestamp 
imu.IMURead()
timestamp_p = imu.getIMUData()["timestamp"]

try:
    while True:
        if imu.IMURead():
            print("Static: ", static)
            if static == True:
                imu.setSlerpPower(0.5)
            else:
                imu.setSlerpPower(0.0)

            start = time.clock()

            timestamp = imu.getIMUData()["timestamp"]

            fusionQPose = imu.getMeasuredQPose()  
            #Library is quaternion scalar first, we need scalar last -> hack
            fusionQPose = fusionQPose[1:] + fusionQPose[:1]          
            ax, ay, az = imu.getAccel()


            fusionPose = imu.getMeasuredPose()
            print("r: {:3f} p: {:3f} y: {:3f}".format(math.degrees(fusionPose[0]), math.degrees(fusionPose[1]), math.degrees(fusionPose[2])))

            r = R.from_quat(fusionQPose)

            traslational_accelerations = r.apply(np.array([ax, ay, az])) * 9.81

            # Remove gravity
            traslational_accelerations[2] = traslational_accelerations[2] - 10.075
            print("ax: {:8f} ay: {:8f} az: {:8f}".format(ax, ay, ax))
            print("tax: {:8f} tay: {:8f} taz: {:8f}".format(traslational_accelerations[0], traslational_accelerations[1], traslational_accelerations[2]))
            # Calculate acceleration magnitude vector to check if static
            amag = magnitude_acceleration(ax, ay, az) 
            print("Amag: {}".format(amag))
            if amag < threshold: 
                static = True
                #force zero velocity
                velocity = np.array([0,0,0])
            else:
                static = False
                velocity = velocity + traslational_accelerations * poll_interval
            #Integrate once to obtain velocity
            print(velocity)

            #Integrate again to obtain displacement
            position = position + velocity * poll_interval
            print("Position:", position)

            timestamp_p = timestamp
            end = time.clock() 
            time.sleep(poll_interval*1.0/1000.0 - (end - start))


except KeyboardInterrupt:
    print("Exit and save data dump")
    f.close()