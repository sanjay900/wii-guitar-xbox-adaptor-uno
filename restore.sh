sudo dfu-programmer atmega16u2 erase --force
sudo dfu-programmer atmega16u2 flash /usr/share/arduino/hardware/archlinux-arduino/avr/firmwares/atmegaxxu2/arduino-usbserial/Arduino-usbserial-uno.hex
sudo dfu-programmer atmega16u2 reset
