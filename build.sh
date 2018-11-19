#!/bin/bash

echo "----) Building synthmark..."
NDK=~/Android/Sdk/ndk-bundle/ndk-build
APP=$(pwd)/android_mk

source ./goRoot.sh

cd $APP
$NDK clean
$NDK
adb push ./libs/arm64-v8a/synthmark /data/
echo "----------------"
echo
