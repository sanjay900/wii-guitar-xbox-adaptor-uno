#include <NintendoExtensionCtrl.h>
#include "WiiExtension.h"
#include "util.h"
WiiExtension controller;
WiiController data;
void setup()
{
  pinMode(A3, OUTPUT); 
  digitalWrite(A3, HIGH);
  Wire.begin();
  Wire.setClock(360000);
  controller.setup();
  Serial.begin(500000);
}
void loop()
{
  controller.read_controller(&data);
  Serial.print("ma");
  Serial.write((uint8_t*)&data, sizeof(data));
}
