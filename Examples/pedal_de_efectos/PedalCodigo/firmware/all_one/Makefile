LM32_CC=lm32-elf-gcc
LM32_LD=lm32-elf-ld
LM32_OBJCOPY=lm32-elf-objcopy
LM32_OBJDUMP=lm32-elf-objdump

SREC2VRAM ?= ../../tools/srec2vram/srec2vram

VRAMFILE=image.ram

CFLAGS=-MMD -O2 -Wall -s -fomit-frame-pointer -mbarrel-shift-enabled   -mmultiply-enabled -mdivide-enabled -msign-extend-enabled
LDFLAGS=-nostdlib -nodefaultlibs -Tlinker.ld 
SEGMENTS = -j .text -j .rodata -j .data

all: $(VRAMFILE) 

crt0ram.o: crt0ram.S
	$(LM32_CC) $(CFLAGS) -c crt0ram.S

main.o: main.c
	$(LM32_CC) $(CFLAGS) -c main.c

all_one.o: all_one.c
	$(LM32_CC) $(CFLAGS) -c all_one.c

image: crt0ram.o main.o all_one.o
	$(LM32_LD) $(LDFLAGS) -Map image.map -N -o image crt0ram.o main.o all_one.o

image.lst: image
	$(LM32_OBJDUMP) -h -S $< > $@

image.bin: image
	$(LM32_OBJCOPY) $(SEGMENTS) -O srec image image.bin

image.srec: image image.lst
	$(LM32_OBJCOPY) $(SEGMENTS) -O srec image image.srec

$(VHDLFILE): image.srec
	$(SREC2VHDL) image.srec > $(VHDLFILE)

$(VRAMFILE): image.srec
	$(SREC2VRAM) image.srec 0x00000000 0x4000 > $(VRAMFILE)

clean:
	rm -f image image.lst image.bin image.srec image.map  *.o *.d

DEPS := $(wildcard *.d)
ifneq ($(DEPS),)
include $(DEPS)
endif

