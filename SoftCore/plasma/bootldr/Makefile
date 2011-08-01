VHDL_DIR  = ../logic
TOOLS_DIR = ../bin
LIB_DIR   = ../lib
TARGET    = bootldr
CROSS     = mips-elf
GCC       = $(CROSS)-gcc
AS        = $(CROSS)-as
LD        = $(CROSS)-ld
DUMP      = $(CROSS)-objdump
OBJCOPY   = $(CROSS)-objcopy
INC_PATH  = ../include
CFLAGS    = -O2 -I$(INC_PATH) -Wall -c -s 
ILDFLAGS  = -Ttext 0 -eentry -Map $@.map -s -N
LDFLAGS   = -Ttext 0x10000000 -eentry -Map $@.map -s -N

#Internal RAM 0x00
#External RAM 0x10000000

vpath %.c $(LIB_DIR)
vpath %.S $(LIB_DIR)

.c.o:
	$(GCC) $(CFLAGS) $< 
.S.o:
	$(AS)  -o $@ $< 

all: $(TARGET)

clean: 
	-rm -rf *.o *.txt *.map *.lst *.bin opcodes_iram opcodes_ram test bootldr

$(TARGET): crt0.o $(TARGET).o no_os.o ddr_init.o
	$(LD) $(ILDFLAGS) -o $@ $^
	$(OBJCOPY) -I elf32-big -O binary $@ $@.bin

vhdl_mem: $(TARGET)
	$(TOOLS_DIR)/ramimage $(VHDL_DIR)/ram_xilinx.vhd $^.bin $(VHDL_DIR)/ram_image.vhd

upload: $(TARGET)
	sudo cat $^.bin > /dev/ttyUSB0

run: $(TARGET)
	$(TOOLS_DIR)/mlite $^.bin 
