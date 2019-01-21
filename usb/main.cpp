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
}
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "bootloader.h"
#define RXLED 4
#define TXLED 5

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

uint8_t current_control;
ISR(USART1_RX_vect) {
  char data = UDR1;
  switch (current_control) {
  case 0:
    if (data == 'm' || data == 'b') {
      current_control++;
    }
    break;
  case 1:
    if (data == 'o') {
      bootloader();
    }
    if (data == 'a')
      current_control++;
    else
      current_control = 0;
    break;
  case 2:
    gamepad_state.digital_buttons_1 = data;
	current_control++;
    break;
  case 3:
    gamepad_state.digital_buttons_2 = data;
	current_control++;
    break;
  case 4:
    gamepad_state.lt = data * 2;
	current_control++;
    break;
  case 5:
    gamepad_state.rt = data * 2;
	current_control++;
    break;
  case 6:
    gamepad_state.l_x = (data - 128) * 256;
	current_control++;
    break;
  case 7:
    gamepad_state.l_y = (data - 128) * 256;
	current_control++;
    break;
  case 8:
    gamepad_state.r_x = data;
	current_control++;
    break;
  case 9:
    gamepad_state.r_x = (data << 8 | gamepad_state.r_x ) - 32768;
	current_control++;
    break;
  case 10:
    gamepad_state.r_y = data;
	current_control++;
    break;
  case 11:
    gamepad_state.r_y = (data << 8 | gamepad_state.r_y) - 32768;
    current_control = 0;
    break;
  }
  xbox_reset_watchdog();
  xbox_send_pad_state();
}

void USART_Init(uint16_t baudSetting) {
  // Set baud rate
  UBRR1 = baudSetting;
  // Enable receiver
  UCSR1B = (1 << RXEN1);
  // Set frame format: 8data, 1stop bit
  UCSR1C = (1 << UCSZ10) | (1 << UCSZ11);
}

int main(void) {

  USART_Init(1);
  // Set clock @ 16Mhz
  CPU_PRESCALE(0);

  // Init XBOX pad emulation
  xbox_init(true);
  UCSR1B |= (1 << RXCIE1);
  sei();
  for (;;) {}
}