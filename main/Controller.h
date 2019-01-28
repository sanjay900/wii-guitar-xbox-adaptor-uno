#pragma once
#include <inttypes.h>

typedef struct {
  uint8_t digital_buttons_1;
  uint8_t digital_buttons_2;
  uint8_t l_tr;
  uint8_t r_tr;
  uint8_t l_x;
  uint8_t l_y;
  uint8_t r_x;
  uint8_t r_y;
} Controller;

#define XBOX_DPAD_UP		0x01
#define XBOX_DPAD_DOWN		0x02
#define XBOX_DPAD_LEFT		0x04
#define XBOX_DPAD_RIGHT		0x08
#define XBOX_START			0x10
#define XBOX_BACK			0x20
#define XBOX_LEFT_STICK		0x40
#define XBOX_RIGHT_STICK	0x80

// digital_buttons_2
#define XBOX_LB		0x01
#define XBOX_RB		0x02
#define XBOX_HOME	0x04
#define XBOX_A		0x10
#define XBOX_B		0x20
#define XBOX_X		0x40
#define XBOX_Y		0x80