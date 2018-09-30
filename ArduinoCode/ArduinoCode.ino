#include <NintendoExtensionCtrl.h>
#include "WiiExtension.h"
#include "UnoJoy.h"
WiiExtension controller;
WiiController data;
void setup()
{
  pinMode(A3, OUTPUT); 
  digitalWrite(A3, HIGH);
  controller.setup();
  setupUnoJoy();
}
void loop()
{
  controller.read_controller(&data);
  setControllerData(data);
}
