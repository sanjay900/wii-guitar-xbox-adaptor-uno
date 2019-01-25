#include "Controller.h"
#include "util.h"
#include "util/delay.h"
#include "wii/WiiExtension.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include "twi/I2Cdev.h"
extern "C" {
#include "uart/uart.h"
}

WiiExtension controller;

Controller data;
int main() {
  sei();
  uart_init();
  controller.init();
  DDRD &= ~(_BV(2));
  PORTD |= _BV(2);
  for (;;)
  {
    if (controller.read_controller(&data) || bit_is_clear(PIND, 2)) {
      uart_putstr("bo");
      for (;;){}
    }
    uart_putstr("ma");
    for (uint8_t i=0; i < sizeof(data); i++) {
      uart_putchar(((uint8_t*)&data)[i]);
    }
  }
}
