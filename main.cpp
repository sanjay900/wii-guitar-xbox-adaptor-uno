/*
     .k8GOGGNqkSFS5XkqXPSkSkkqXXFS5kSkSS15U22F2515U2uujuu1U1u2U1U2uUuFS.
   :0qE     JS5uuJuuFFX51jU2SSk12jU2SSXF5uuu15SFS5k12ujj21S5kFS5S12jJYu11
  5XS:        1UYYLu.   vUUX    U22r     SUF         SUF           ;YYLuU5
 1F5i  NNSkS7  2uLJui   51u     S5.      .PX         .XX           LJvLLu1.
 kUk  0iLk5FFu vuYY2:   5F    Xkk7        78    E0    i0    GEXPXk2uLLvLLuk
X25, 8O   2kX0  5YJUi   M    555    PkXk   i    q1FU   7    ONNkP12YLvLvLYS
S25  8888  888  5uY5         FuS    PS50   .    FuUU   7          uJvLvLLJ2i
kUF             SJjU.      P02UF    P25k   .    Su2Y   v          2LLvLvLL17
S21  XJj88  0u  1uY2.        X2k           .    k11E   v    7;ii:JuJvLvLvJ2:
2257 jqv   Pqq  1LJur         PP.          7    EX:    q    OqqXP51JYvLvYYS.
 X2F  kXkXSXk  kJYLU:   O     ,Z    0PXZ   i    ii    q0    i:::,,.jLLvLLuF'
 ik1k  ;qkPj  .uJvYu:   UN      :   XU2F   :         S5S           iJLLvjUF8
  :PSq       72uLLLui   uSi    .;   2uY1   r.       72j1           LYYLYJSU88
    XqE2   rP12juJuu1FX55U5FqXXSXkXF1juUkkPSXSPXPXPF1Jju5FkFSFXFSF5uujUu5j28V
      .uGOZESS5S5SFkkPkPkXkPXqXPXqXXFkSkkPXPXPkqSkSS1521252121U2u2u12Suv7

*
* Arduino Micro (Leonardo) XInput Pad Emulator firmware
*
* Copyright (c) 2017
* Bruno Freitas - bruno@brunofreitas.com
* Jon Wilson    - degenatrons@gmail.com
* Kevin Mackett - kevin@sharpfork.com
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
extern "C" {
	#include "XInputPad.h"
	#include "util.h"
}
#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include "WiiController.h"
#define RXLED 4
#define TXLED 5

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

// Initializes the USART to receive and transmit,
//  takes in a value you can find in the datasheet
//  based on desired communication and clock speeds
void USART_Init(uint16_t baudSetting){
	// Set baud rate
	UBRR1 = baudSetting;
	// Enable receiver and transmitter
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	// Set frame format: 8data, 1stop bit
	UCSR1C = (1<<UCSZ10)|(1<<UCSZ11);	
}

// This reads the USART serial port, returning any data that's in the
//  buffer, or a guaranteed zero if it took longer than timeout ms
//  Input: uint_16 timeout - milliseconds to wait for data before timing out
unsigned char serialRead( uint16_t timeout ){
	// Wait for data to be received 
	while ( !(UCSR1A & (1<<RXC1)) ){
		_delay_ms(1);
		timeout--;
		if (timeout == 0){
			return 0b0;
		}			
	}	
	// Get and return received data from buffer 
	return UDR1;
}

// This sends out a byte of data via the USART.
void serialWrite( unsigned char data )
{
	// Wait for empty transmit buffer
	while ( !( UCSR1A & (1<<UDRE1)) ){
	}	
	// Put data into buffer, sends the data
	UDR1 = data;
}

void flushSerialRead()
{
	unsigned char dummy;
	while ( UCSR1A & (1<<RXC1) )
		dummy = UDR1;
}

// This turns on one of the LEDs hooked up to the chip
void LEDon(char ledNumber){
	DDRD |= 1 << ledNumber;
	PORTD &= ~(1 << ledNumber);
}

// And this turns it off
void LEDoff(char ledNumber){
	DDRD &= ~(1 << ledNumber);
	PORTD |= 1 << ledNumber;
}
int main(void) {
	USART_Init(3);
	// Set clock @ 16Mhz
	CPU_PRESCALE(0);

	// Init XBOX pad emulation
	xbox_init(true);

	// Pins polling and gamepad status updates
	for (;;) {
		xbox_reset_watchdog();
		LEDon(TXLED);
		flushSerialRead();
		serialWrite(0);
		gamepad_state.digital_buttons_1 = serialRead(25);
		serialWrite(1);
		gamepad_state.digital_buttons_2 = serialRead(25);
		serialWrite(2);
		gamepad_state.lt = serialRead(25)*2;
		serialWrite(3);
		gamepad_state.rt = serialRead(25)*2;
		serialWrite(4);
		gamepad_state.l_x = (serialRead(25)-128)*256;
		serialWrite(5);
		gamepad_state.l_y = (serialRead(25)-128)*256;
		serialWrite(7);
		gamepad_state.r_x = serialRead(25);
		serialWrite(6);
		gamepad_state.r_x = (gamepad_state.r_x << 8 | serialRead(25))-32768;
		if (gamepad_state.r_x < 0) {
			gamepad_state.r_x = -32768;
		}
		serialWrite(9);
		gamepad_state.r_y = serialRead(25);
		serialWrite(8);
		gamepad_state.r_y = (gamepad_state.r_y << 8 | serialRead(25))-32768;
		LEDoff(TXLED);
		xbox_send_pad_state();
	}
}