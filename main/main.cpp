#include "Controller.h"
#include "twi/I2Cdev.h"
#include "util.h"
#include "util/delay.h"
#include "wii/WiiExtension.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
extern "C" {
#include "uart/uart.h"
}

WiiExtension controller;

volatile int i = 0;
Controller data;
int main() {
  sei();
  uart_init();
  controller.init();
  for (;;) {
    controller.read_controller(&data);
    data.l_tr = rand();
    i = 0;
    UCSR0B = _BV(TXEN0) | _BV(UDRIE0);
  }
}
ISR(USART_UDRE_vect) {
  uint8_t a = UDR0;
  if (i < 2) {
    UDR0 = i == 0 ? 'm' : 'a';
  } else {
    UDR0 = ((uint8_t *)&data)[i - 2];
  }
  i++;
  if (i >= sizeof(data) + 2) {
    UCSR0B = _BV(TXEN0);
  }
}
