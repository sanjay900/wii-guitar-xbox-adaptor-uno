#pragma once
#include "../Controller.h"
#include "../twi/I2Cdev.h"
#include "util/delay.h"
#include "../mpu6050/mpu.h"
#include "NintendoExtensionCtrl.h"

class WiiExtension {
public:
  ExtensionPort port;
  Nunchuk::Shared nchuk;
  ClassicController::Shared classic;
  DrumController::Shared drum;
  GuitarController::Shared guitar;
  DJTurntableController::Shared dj;

  bool read_controller(Controller *controller);
  WiiExtension();
  void init();
};