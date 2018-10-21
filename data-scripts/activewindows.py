import sys
import serial
import time
import re
from os.path import join, dirname
import pyaudio
from datetime import datetime
from threading import Thread, Lock

import numpy as np
import pyaudio
import soundfile
import struct

sys.path.append(join(dirname(__file__), 'Porcupine/binding/python'))

from porcupine import Porcupine

library_path = join(dirname(__file__), 'Porcupine/lib/mac/x86_64/libpv_porcupine.dylib')

# Globally accessible
ser = serial.Serial('/dev/cu.usbmodem1411', 9600, timeout=5)

serial_lock = Lock()


def keywordMonitoring():
    model_file_path = join(dirname(__file__), 'Porcupine/lib/common/porcupine_params.pv')
    keyword_file_paths = ["Porcupine/Hey mate_mac.ppn"]
    sensitivities = [0.8]
    handle = Porcupine(library_path, model_file_path, keyword_file_paths=keyword_file_paths, sensitivities=sensitivities)

    num_keywords = 1
    pa = pyaudio.PyAudio()
    audio_stream = pa.open(
        rate=handle.sample_rate,
        channels=1,
        format=pyaudio.paInt16,
        input=True,
        frames_per_buffer=handle.frame_length,
        input_device_index=None)

    while True:
        pcm = audio_stream.read(handle.frame_length)
        pcm = struct.unpack_from("h" * handle.frame_length, pcm)

        # if self._output_path is not None:
        #     self._recorded_frames.append(pcm)

        result = handle.process(pcm)
        if num_keywords == 1 and result:
            print('[%s] detected keyword' % str(datetime.now()))
            # Send keyword trigger
            # This will block if the serial port hits at the same time
            serial_lock.acquire()
            ser.write(bytes("g", 'utf-8'))
            serial_lock.release()

def eventMonitoring():
    # Thread variables
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
                serial_lock.acquire()
                ser.write(bytes("a","UTF-8"))
                serial_lock.release()
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
                serial_lock.acquire()
                ser.write(bytes("s","UTF-8"))
                serial_lock.release()
            elif zone_entered and not zone_state_changed and zone_time_elapsed > 10:
                serial_lock.acquire()
                ser.write(bytes("d","UTF-8"))
                serial_lock.release()
                zone_state_changed = True

try:
   
   Thread(target=keywordMonitoring).start()
   Thread(target=eventMonitoring).start()

except:
   print ("Error: unable to start thread")
# ./testscript.sh | python3 activewindows.py
