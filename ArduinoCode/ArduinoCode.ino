#include <NintendoExtensionCtrl.h>
#include "WiiExtension.h"
#include "UnoJoy.h"
WiiExtension controller;
WiiController data;
void setup()
{
  pinMode(4, INPUT_PULLUP); 
  controller.setup();
  setupUnoJoy();
}
void loop()
{
  controller.read_controller(&data);
  setControllerData(data);
}
