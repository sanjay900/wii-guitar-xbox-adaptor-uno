#ifndef _WiiCxtension_H_
#define _WiiCxtension_H_
#include <inttypes.h>
typedef struct {
  uint8_t digital_buttons_1;
  uint8_t digital_buttons_2;
  uint8_t lt;
  uint8_t rt;
  uint8_t l_x;
  uint8_t l_y;
  uint16_t r_x;
  uint16_t r_y;
} WiiController;
#endif
