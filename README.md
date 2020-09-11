# Azsphere-Utility

Azure sphere utility is a utility used to set up and control the azure sphere function on EAS-M1.

# Installing

Download the excutable file from bin folder.

# Quick Start

The command currently supported can be list by:
```sh
./azutility -h
```
To check EAS-M1's firmware version if connected as /dev/ttyUSB0 (default):
```sh
./azutility -d --ATI
```
To check EAS-M1's firmware version if connected as /dev/ttyS0:
```sh
./azutility -s /dev/ttyS0 --ATI
```
To add AP info for EAS-M1's WiFi connection:
```sh
./azutility -d --SSID ssid --PSK password -J
```
