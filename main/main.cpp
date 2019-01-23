#include "wii/WiiExtension.h"
#include "wii/WiiExtensions.h"
#include "Controller.h"
#include "util.h"
#include <stdio.h>
#include <avr/sfr_defs.h>
#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>

extern "C"
{
#include "uart.h"
#include "twi/TWIlib.h"
}

WiiExtension controller;

Controller data;
int main()
{
  sei();
  uart_init();
  DDRD &= ~(_BV(2));
  PORTD |= _BV(2);
  controller.setup();
  controller.connect();
  for (;;)
  {
    controller.read_controller(&data);
  }
  // for (;;)
  // {
  //   if (bit_is_clear(PIND, 2)) {
  //     uart_putstr("bo");
  //     for (;;){}
  //   }
  //   uart_putstr("ma");
  //   for (uint8_t i=0; i < sizeof(data); i++) {
  //     uart_putchar(((uint8_t*)&data)[i]);
  //   }
  // }
}
