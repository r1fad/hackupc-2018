#!/bin/bash
for i in `seq 1 5`;
  do
	echo $i
	echo `osascript GetActiveWindows.scpt`
	sleep 1
done
