#ifndef _WiiExtension_H_
#define _WiiExtension_H_
#include <NintendoExtensionCtrl.h>
#include "WiiController.h"
class WiiExtension {
  public:
  ExtensionController extension;
  Nunchuk::Data nchuk = Nunchuk::Data(extension);
  ClassicController::Data classic = ClassicController::Data(extension);
  DrumController::Data drum = DrumController::Data(extension);
  GuitarController::Data guitar = GuitarController::Data(extension);
  DJTurntableController::Data dj = DJTurntableController::Data(extension);
  void read_controller(WiiController* controller);
  void setup();
};
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
#endif
