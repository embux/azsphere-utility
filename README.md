# Azsphere-Utility

Azure sphere utility is a utility used to set up and control the azure sphere function on EAS-M1.

# Installing

Download the excutable file from bin folder.

# Quick Start

The command currently supported can be list by:
```sh
./azutility -h
```

```sh
Usage: azutility [-d] [-s dev_node] [--AT] [--ATI] [-S] [-D] [-A] [--SSID ssid --PSK psk -J] [-C connect_string] [-h] [-v]
        --AT                 Send AT Check
        --ATI                Send ATI Check
  -s,   --setPort            Set serial port device node
  -d,   --defPort            Use default serial port device node (/dev/ttyUSB0)
  -S,   --AT_CWLAP           Scan Access Point
  -D,   --AT_CWDAP           Delete all stored AP info
  -A,   --AT_CWAAP           List all stored AP info
  -J,   --AT_CWJAP           Add AP info ( Input AP info using --SSID and --PSK )
  -C,   --AT_ACCS            Setup Connection String
  -Q,   --AT_CWSQ            Setup Connection String
  -C,   --AT_ACWR            Send Message to Azure IoT Hub
  -h,   --help               Display this help and exit
  -v,   --version            Output version information and exit
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
