#!/bin/bash

set -e

source ./goRoot.sh

./build.sh

./toggleWALT.sh 0

echo "----) Creating cpuset cgroup..."
adb shell '
ls /dev/cpuset > /dev/null
if [ "$?" -ne "0" ]; then
	echo "Creating /dev/cpuset"
	mkdir /dev/cpuset
	mount -t cgroup -o cpuset cpuset /dev/cpuset
else
	echo "/dev/cpuset exists!"
fi

cd /dev/cpuset

ls dl > /dev/null
if [ "$?" -ne "0" ]; then
	echo "Creating /dev/cpuset/dl"
	mkdir dl
else
	echo "/dev/cpuset/dl exists!"
fi

cpus="6"
echo "Setting cpus = [$cpus]"
echo $cpus > dl/cpus
'

echo "----------------"
echo
echo "----) Running synthmark tests..."
# LatencyMark
adb shell '
echo 0 > /dev/cpuset/dl/mems
echo $$ > /dev/cpuset/dl/tasks
echo /dev/cpuset/dl/cpus: $(cat /dev/cpuset/dl/cpus)
echo /dev/cpuset/dl/tasks: $(cat /dev/cpuset/dl/tasks)
cd /data/

#sleep 1
#./synthmark -tv -s20 -p95

#./synthmark -h
sleep 1
./synthmark -s60 -b64 -B20 -tl -n5 -N185 -mr
#sleep 5
#./synthmark -s60 -b64 -tl -n5 -N130 -ml
#sleep 5
#./synthmark -s60 -b64 -tl -n5 -N130 -mr
'
# JitterMark
#adb shell "cd /data/; ./synthmark -tj -n80"
# VoiceMark
#adb shell "cd /data/; ./synthmark -tv -s20 -p90"
# UtilizationMark
#adb shell "cd /data/; ./synthmark -tu -n20"
echo

