MCU    = atmega168
CC     = avr-gcc
OBJCOPY= avr-objcopy
CFLAGS = -g -mmcu=$(MCU) -Wall -Wstrict-prototypes -O0 -mcall-prologues
BINDIR = binary
TARGET = prog

OBJECTS = main.o

.PHONY: all 

all: $(TARGET).hex

prog.hex : main.out 
	$(OBJCOPY) -R .eeprom -O ihex main.out $(BINDIR)/$(TARGET).hex 
	
main.out : $(OBJECTS) 
	$(CC) $(CFLAGS) -o main.out -Wl,-Map,main.map $(OBJECTS) -lm
	avr-size main.out

main.o : main.c
	$(CC) $(CFLAGS) -Os -c main.c

clean:
	rm -f *.o *.map *.out *.hex $(BINDIR)/$(TARGET).hex
