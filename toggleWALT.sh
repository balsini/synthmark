#!/bin/bash

source ./goRoot.sh

echo "----) Setting WALT to $1..."
adb shell "grep '' /proc/sys/kernel/sched_use_walt_*"

adb shell "echo $1 > /proc/sys/kernel/sched_use_walt_task_util"
adb shell "echo $1 > /proc/sys/kernel/sched_use_walt_cpu_util"

adb shell "grep '' /proc/sys/kernel/sched_use_walt_*"
echo "----------------"
echo
