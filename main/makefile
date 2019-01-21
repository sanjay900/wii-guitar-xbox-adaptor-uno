MCU         = atmega328p
TARGET_ARCH = -mmcu=$(MCU)
OBJDIR		 = obj
BIN		 	 = bin
TARGET      = $(BIN)/main
CC          = avr-gcc
CPPFLAGS    = -mmcu=$(MCU)
CFLAGS      = -Os -g -Wall -I. -DF_CPU=16000000
LDFLAGS     = -g -mmcu=$(MCU) -lm -Wl,--gc-sections -Os
PGMER       = -c arduino -b 115200 -P /dev/ttyACM0
PGMERISP    = -c avrispv2 -P /dev/ttyACM0
DUDE        = /usr/bin/avrdude -V -p $(MCU)

C_SRCS      = $(wildcard *.c)
OBJ_FILES2   = $(C_SRCS:.c=.o)
OBJ_FILES   = $(OBJ_FILES2:%=$(OBJDIR)/%)
$(info $(shell mkdir -p $(BIN) $(OBJDIR)))
all:    $(TARGET).hex

clean:
	rm -rf $(BIN) $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_FILES)

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" -O ihex bin/main.elf bin/eeprom.hex

upload: $(TARGET).hex
	$(DUDE) $(PGMER) -U flash:w:main.hex

size: main.elf
	avr-size --format=avr --mcu=$(MCU) main.elf