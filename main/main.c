// #include <NintendoExtensionCtrl.h>
// #include "WiiExtension.h"
#include "WiiController.h"
#include "util.h"
#include <stdio.h>
#include <avr/sfr_defs.h>
#include <avr/io.h>
#include "uart.h"
// WiiExtension controller;

WiiController data;
void setup()
{
  // pinMode(A3, OUTPUT);
  // digitalWrite(A3, HIGH);
  // Wire.begin();
  // Wire.setClock(360000);
  // controller.setup();
  // Serial.begin(500000);
}
int main()
{
  uart_init();
  DDRD &= ~(_BV(2));
  PORTD |= _BV(2);
  // controller.read_controller(&data);
  for (;;)
  {
    if (bit_is_clear(PIND, 2)) {
      uart_putstr("bo");
      for (;;){}
    }
    uart_putstr("ma");
    for (uint8_t i=0; i < sizeof(data); i++) {
      uart_putchar(((uint8_t*)&data)[i]);
    }
  }
}
