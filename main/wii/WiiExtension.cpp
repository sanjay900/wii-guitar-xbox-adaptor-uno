#include "WiiExtension.h"
#include "../util.h"
#include <util/delay.h>
#define constrain(amt, low, high)                                              \
  ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

WiiExtension::WiiExtension()
    : nchuk(port), classic(port), dj(port), guitar(port), drum(port) {}
void WiiExtension::init() {
  I2Cdev::TWIInit();
  mympu_open(10);
}
void WiiExtension::read_controller(Controller *controller) {
  if (!port.update()) {
    port.connect();
    return;
  }
  switch (port.getControllerType()) {
  case (ExtensionType::DJTurntableController):
    break;
  case (ExtensionType::Nunchuk):
    bit_write(nchuk.buttonC(), controller->digital_buttons_2, XBOX_A);
    bit_write(nchuk.buttonZ(), controller->digital_buttons_2, XBOX_B);
    controller->l_x = nchuk.joyX() * 8;
    controller->l_y = nchuk.joyY() * 8;
    controller->r_x = (nchuk.rollAngle() + 180);
    controller->r_y = (nchuk.pitchAngle() + 180);
    break;
  case (ExtensionType::DrumController):
    controller->l_x = drum.joyX() * 8;
    controller->l_y = drum.joyY() * 8;
    bit_write(drum.drumGreen(), controller->digital_buttons_2, XBOX_A);
    bit_write(drum.drumRed(), controller->digital_buttons_2, XBOX_B);
    bit_write(drum.cymbalYellow(), controller->digital_buttons_2, XBOX_Y);
    bit_write(drum.drumBlue(), controller->digital_buttons_2, XBOX_X);
    bit_write(drum.cymbalOrange(), controller->digital_buttons_2, XBOX_LB);
    bit_write(drum.bassPedal(), controller->digital_buttons_2, XBOX_RB);
    bit_write(drum.buttonPlus(), controller->digital_buttons_1, XBOX_START);
    bit_write(drum.buttonMinus(), controller->digital_buttons_1, XBOX_BACK);
    break;
  case (ExtensionType::GuitarController):
    controller->r_x = 128 - ((guitar.whammyBar() - 14) * 8);
    if (guitar.whammyBar() <= 18) {
      controller->r_x = 128;
    }
    if (counter % 20 == 0) {
      double z;
      mympu_update();
      z = (mympu.ypr[2] * (128 / M_PI));
      if (z > 128) z = 0;
      z = z * 2;
      if (z > 128) z = 256 - z;
      z = pow(z, 1.1f);
      z = constrain(z, 0, 128);
      controller->r_y = (uint8_t)(z);
    }
    counter++;
    bit_write(guitar.strumUp() || guitar.joyY() > 40,
              controller->digital_buttons_1, XBOX_DPAD_UP);
    bit_write(guitar.strumDown() || guitar.joyY() < 20,
              controller->digital_buttons_1, XBOX_DPAD_DOWN);
    bit_write(guitar.joyX() < 20, controller->digital_buttons_1,
              XBOX_DPAD_LEFT);
    bit_write(guitar.joyX() > 40, controller->digital_buttons_1,
              XBOX_DPAD_RIGHT);
    bit_write(guitar.buttonPlus(), controller->digital_buttons_1, XBOX_START);
    bit_write(guitar.buttonMinus(), controller->digital_buttons_1, XBOX_BACK);
    bit_write(guitar.fretGreen(), controller->digital_buttons_2, XBOX_A);
    bit_write(guitar.fretRed(), controller->digital_buttons_2, XBOX_B);
    bit_write(guitar.fretYellow(), controller->digital_buttons_2, XBOX_Y);
    bit_write(guitar.fretBlue(), controller->digital_buttons_2, XBOX_X);
    bit_write(guitar.fretOrange(), controller->digital_buttons_2, XBOX_LB);
    break;

  case (ExtensionType::ClassicController):
    controller->l_x = classic.leftJoyX() * 4;
    controller->l_y = classic.leftJoyY() * 4;
    controller->r_x = classic.rightJoyX() * 8;
    controller->r_y = classic.rightJoyY() * 8;
    controller->l_tr = classic.triggerL() * 8;
    controller->r_tr = classic.triggerR() * 8;
    bit_write(classic.dpadUp(), controller->digital_buttons_1, XBOX_DPAD_UP);
    bit_write(classic.dpadDown(), controller->digital_buttons_1,
              XBOX_DPAD_DOWN);
    bit_write(classic.dpadLeft(), controller->digital_buttons_1,
              XBOX_DPAD_LEFT);
    bit_write(classic.dpadRight(), controller->digital_buttons_1,
              XBOX_DPAD_RIGHT);
    bit_write(classic.buttonStart(), controller->digital_buttons_1, XBOX_START);
    bit_write(classic.buttonSelect(), controller->digital_buttons_1, XBOX_BACK);
    bit_write(classic.buttonHome(), controller->digital_buttons_2, XBOX_HOME);
    bit_write(classic.buttonA(), controller->digital_buttons_2, XBOX_A);
    bit_write(classic.buttonB(), controller->digital_buttons_2, XBOX_B);
    bit_write(classic.buttonY(), controller->digital_buttons_2, XBOX_Y);
    bit_write(classic.buttonX(), controller->digital_buttons_2, XBOX_X);
    bit_write(classic.buttonZL(), controller->digital_buttons_2, XBOX_LB);
    bit_write(classic.buttonZR(), controller->digital_buttons_2, XBOX_RB);
    break;
  default:
    break;
  }
}
