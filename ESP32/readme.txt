The YAML files in this directory are for configuring the ESP32 modules.

Related software and websites:

https://esphome.io/guides/getting_started_command_line.html

https://github.com/esphome/esphome-flasher

On the first flash of an ESP32, it needs to be plugged in via a USB cable (subsequent flashings are OTA). Some observations: 

- the --privileged flag may be needed for docker to have access to the usb device
- make sure the usb cable supports data, some are power only
- if all else fails flash the esp32 using esphome-flasher with the .bin file generated from the command line (check timestamps!) 
- the arduino app can be useful to find the serial port for the esp32


