# Wiitar Xbox360 Adapter - UNO Version
![https://github.com/sanjay900/wii-guitar-xbox-adaptor-uno](https://github.com/sanjay900/wii-guitar-xbox-adaptor-uno)

This project aims to provide an adapter that when used will expose a wii guitar hero controller as an xbox 360 controller, so that games such as Clone Hero can immediately use these controllers without calibration. This repo is for the arduino uno, or other devices that use an atmega16u2. Check https://github.com/sanjay900/wii-guitar-xbox-adaptor for the direct USB version

# How to use this repo
## You will need:
1. An Arduino uno
2. A wii extension cable or breakout board
3. A AM3x accelerometer

## Setting up an Arduino IDE
1. Install https://github.com/dmadison/NintendoExtensionCtrl
2. Upload the sketch inside ArduinoCode to the Arduino
3. Set your uno into DFU mode (https://www.arduino.cc/en/Hacking/DFUProgramming8U2). Note that the "eleven" compatible boards require bridging the reset pins, holding the reset button, releasing the reset pins and then releasing the button.
5. run make dfu to upload the hid firmware to the arduino

## Building the hardware
1. Find the I2C pins on your Arduino, and connect them to the extension / breakout board. Also connect ground to ground and 3.3v to 3.3v on the Arduino.
2. Connect the accelerometer to the analogue pins of the arduino. Note that the ground pin needs to be connected seperately, as there are not enough analogue pins as the arduino shares them with I2C.