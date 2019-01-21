#include <avr/io.h>
#include <stdio.h>

/* http://www.cs.mun.ca/~rod/Winter2007/4723/notes/serial/serial.html */

void uart_init(void) {
     // Set baud rate
  UBRR0 = 1;
  // Enable transmitter
  UCSR0B = _BV(TXEN0);
  // Set frame format: 8data, 1stop bit
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

void uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r', stream);
    }
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

char uart_getchar(FILE *stream) {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}
