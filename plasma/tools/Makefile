CC_X86      = gcc -Wall -O -g
CP          = cp
RM          = rm -rf 
DWIN32      =
BIN_MIPS    = 
VHDL_DIR    = ../logic
LINUX_PWD   = ./
CONVERT_BIN = $(LINUX_PWD)convert_bin

CFLAGS = -O2 -Wall -c -s 

all: ramimage mlite
	rm -rf ../bin
	mkdir ../bin; mv ramimage ../bin; mv mlite ../bin
	
clean:
	-$(RM) *.o *.obj *.map *.lst *.hex *.txt ../bin

ramimage: ramimage.c
	@$(CC_X86) -o ramimage ramimage.c

mlite: mlite.c
	@$(CC_X86) -o mlite mlite.c

