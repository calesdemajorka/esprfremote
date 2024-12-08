# Description

Simple project to enable control over RF sockets via WiFi.
I don't have the remote, but luckily the author of rc-switch library got it figured out.

# Programming

Programming is done using the arduino-ide, but from the vscode, with proper settings in the [arduino.json](arduino.json).

## Defines

Only ARDUINO=100 define is needed to properly use the arduino extension.

## Include path

The include path is a bit messy because of how arduino is organised. List of paths i used:

```
                "/home/${USER}/Arduino/libraries/**",
                "/home/${USER}/arduino-1.8.12/hardware/tools/**",
                "/home/${USER}/arduino-1.8.12/hardware/arduino/**",
                "/home/${USER}/.arduino15/packages/esp8266/hardware/**"
```

## Module wiring

Before hitting the program button, you need to connect IO0 to GND.

See below for programming:

https://github.com/esp8266/esp8266-wiki/wiki/Uploading

# Modules

The esp8266 module is the version soldered to xpansion board.
![modul-wifi-esp-12e-esp8266-black-adapter-254mm](https://user-images.githubusercontent.com/3448668/147832301-c3239fcc-fb80-4990-9d46-653947eab890.jpg)
![433mhz_rf_transmitting_receiver_module](https://user-images.githubusercontent.com/3448668/147832352-d161d011-2d24-4da0-a674-55390004a326.jpg)

Image sources: [botland](https://www.google.com/url?sa=i&url=https%3A%2F%2Fbotland.com.pl%2Fprodukty-wycofane%2F7381-modul-wifi-esp-12e-esp8266-black-adapter-254mm.html&psig=AOvVaw2j45rqQh0SF_r7CS-p6vby&ust=1641054161393000&source=images&cd=vfe&ved=0CAsQjRxqFwoTCOijw7C6jvUCFQAAAAAdAAAAABAD)
[elecrow](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.elecrow.com%2F433mhz-rf-transmitting-module-p-372.html&psig=AOvVaw1zxgRG3AJPngb0XvC0hrDh&ust=1641054277411000&source=images&cd=vfe&ved=0CAsQjRxqFwoTCIjGgvK5jvUCFQAAAAAdAAAAABAD)
