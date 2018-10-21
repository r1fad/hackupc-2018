import sys
import serial
import time
import re

ser = serial.Serial('/dev/cu.usbmodem1411', 9600, timeout=5)

unsafe_keywords = ["facebook", "twitter", "gmail", "reddit", "quora", "messenger", "9gag"]
safe_keywords = ["atom", "sublime", "terminal", "stack", "overflow", "github", "intellij", "slack", "spotify"]

zone_entered = False
zone_time_elapsed = 0
stackoverflow_updated = False
zone_state_changed = False

# Receive events from Shell Script
for line in sys.stdin: 
    event_string = re.sub("[^A-Za-z0-9]+", ' ', line.lower()).split(" ")
    print (event_string)
    # Keep track of time spent in zone    
    for keyword in event_string:
        if keyword in safe_keywords and zone_entered:
            zone_time_elapsed += 1
        # Zone broken
        if keyword in unsafe_keywords:
            print ("Keyword found")
            ser.write(bytes("a","UTF-8"))
            zone_entered = False
            zone_time_elapsed = 0
            zone_state_changed = False
            stackoverflow_updated = False
        # Detect work started
        elif keyword in safe_keywords:
            print ("Zone entered")
            zone_entered = True
            zone_time_elapsed += 1
            if (keyword == "stack" or keyword == "overflow") and (zone_time_elapsed > 10 and not stackoverflow_updated):
                stackoverflow_updated = True
                zone_time_elapsed += 1
                ser.write(bytes("s", "utf-8"))
        elif zone_entered and not zone_state_changed and zone_time_elapsed > 10:
            ser.write(bytes("d", "utf-8"))
            zone_state_changed = True
# ./testscript.sh | python3 activewindows.py
