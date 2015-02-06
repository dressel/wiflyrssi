# wiflyrssi
This is some C-code that will get rssi data from the RN-XV WiFly module, over serial. I have a WiFly RN-XV connected to an XBee Explorer USB. The XBee Explorer is connected via USB to a computer running Ubuntu. This code allows you to scan for a specific SSID, and returns the rssi value if it is found. If it is not found, it returns the max int value.

This code is very messy and I might make it pretty at some point. At this point this code and documentation exist primarily so I can reference it in the future. However, maybe someone else is struggling to get this to work and it can help them out too.

## How to Screen to WiFly
```
screen /dev/ttyUSB0
```

## How to Close that Screen Process
This closes a screen instead of detaching it.
(ctrl+a), then \

## Troubleshooting
I think you need to be in the dialout group to connect via screen. You can still connect by using sudo:
```
sudo screen /dev/ttyUSB0
```
You can avoid having to use sudo with screen if you add yourself to the dialout group. I can't remember exactly how I did it, but I think it is:
```
sudo adduser your_username dialout
```
It is also possible that the antenna is not connected to /dev/ttyUSB0. To search for other possibilities, use
```
ls /dev/tty*
```
Search for something that has USB in it. 
