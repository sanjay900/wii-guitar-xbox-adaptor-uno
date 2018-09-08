# Wiitar Xbox360 Adapter
![adaptor.jpg](adaptor.jpg)

This project aims to provide an adapter that when used will expose a wii guitar hero controller as an xbox 360 controller, so that games such as Clone Hero can immediately use these controllers without calibration. This repo is for the arduino uno, or other devices that use an atmega16u2. Check https://github.com/sanjay900/wii-guitar-xbox-adaptor for the direct USB version

# How to use this repo
## You will need:
1. An Arduino uno
2. A wii extension cable or breakout board
3. A gravity switch
4. A 2 pin connector (optional)

## Setting up an Arduino IDE
It is recommended to set aside a separate Arduino IDE for this project, as LUFA will overwrite many core Arduino USB files, and as a result will lead to some issues with other sketches.
2. Install https://github.com/dmadison/NintendoExtensionCtrl
3. Upload the sketch inside ArduinoCode to the Arduino
4. Set your uno into DFU mode (https://www.arduino.cc/en/Hacking/DFUProgramming8U2). Note that the "eleven" compatible boards require bridging the reset pins, holding the reset button, releasing the reset pins and then releasing the button.
5. run make dfu to upload the hid firmware to the arduino

## Building the hardware
1. Find the I2C pins on your Arduino, and connect them to the extension / breakout board. Also connect ground to ground and 3.3v to 3.3v on the Arduino.
2. Connect the gravity switch between digital pin 4 and ground. Optionally put some sort of connector between the gravity switch and the Arduino if you would like this to be easily removable.
3. Use double sided tape to adhere the gravity switch to the guitar. Note that the angle the switch is mounted can be used to calibrate when the switch activates, and so it is useful to open some tool that allows you to visualise the right joystick Y axis in order to calibrate this in a way that suits you.