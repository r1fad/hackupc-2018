import sys
import serial
import time

ser = serial.Serial('/dev/cu.usbmodem14101', 9600, timeout=5)
# for line in sys.stdin:
#     sys.stdout.write(line)
#     ser.write(bytes("a","UTF-8"));
#     time.sleep(2)

time.sleep(2)
ser.write(bytes("d","UTF-8"))
print("sent")
time.sleep(10)
ser.write(bytes("a","UTF-8"))
print("sent")
# ./testscript.sh | python3 activewindows.py
