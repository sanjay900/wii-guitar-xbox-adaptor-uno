#pragma once
#include "../Controller.h"
extern "C"
{
#include "../uart.h"
#include <stdio.h>
#include "../twi/TWIlib.h"
}
#include "util/delay.h"
#include "WiiExtensions.h"
class WiiExtension
{
public:
  uint8_t addr = 0x52;
  ExtensionType conType;
  void read_controller(Controller *controller);
  void setup();
  void connect();
};