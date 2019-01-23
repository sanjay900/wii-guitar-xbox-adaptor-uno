#include <avr/interrupt.h>
#include "millis.h"
volatile uint64_t millis_prv = 0;

void millis_init()
{
  TCCR0A = 0;
  // set timer0 with CLKio/8 prescaler
  TCCR0B = _BV(CS01) | _BV(CS00);
  // clear any TOV1 Flag set when the timer overflowed
  TIFR0 &= ~TOV0;
  // set timer0 counter initial value to 0
  TCNT0 = 0x0;
  // enable timer overflow interrupt for Timer0
  TIMSK0 = _BV(TOIE0);
  // clear the Power Reduction Timer/Counter0
  PRR &= ~PRTIM0;
}

// TIMER0 interrupt handler
ISR(TIMER0_OVF_vect)
{
  // reset the counter (overflow is cleared automatically)
  TCNT0 = (uint8_t)(0xFF - ((F_CPU / 8) / 1000)); // use CLKio/8 prescaler (set CS0n accordingly above)
  millis_prv++;
}

// return elapsed time in milliseconds
uint64_t millis()
{
  return millis_prv;
}