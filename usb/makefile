#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

MCU          = atmega16u2
ARCH         = AVR8
BOARD        = UNO
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
SRC          = main.cpp XInputPad.c Descriptors.c bootloader.cpp $(LUFA_SRC_USBCLASS) $(LUFA_SRC_USB)
LUFA_PATH    = ../lufa/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/
LD_FLAGS     =
OBJDIR		 = obj
BIN		 	 = bin
TARGET       = $(BIN)/XInputPadMicro
AVRDUDE_PROGRAMMER = avr109
AVRDUDE_FLAGS = -b 57600 -P /dev/ttyACM0 reset
$(info $(shell mkdir -p $(BIN)))

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk
