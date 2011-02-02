
OBJS	:= start.o main.o jz_serial.o

CROSS	:= mipsel-openwrt-linux-

CFLAGS	:= -O2 -G 0 -mno-abicalls -fno-pic -mips32 -Iinclude
AFLAGS	= -D__ASSEMBLY__ $(CFLAGS)
LDFLAGS	:= -T ld.script -nostdlib -EL

.c.o:
	$(CROSS)gcc $(CFLAGS) -c $< -o $@
.S.o:
	$(CROSS)gcc $(AFLAGS) -c $< -o $@

jz_xloader.bin: jz_xloader
	$(CROSS)objdump -D jz_xloader $< > jz_xloader.dump
	$(CROSS)objcopy -O binary $< $@

jz_xloader: $(OBJS)
	$(CROSS)ld $(LDFLAGS) $^ -o $@

upload: jz_xloader
	sudo usbtool 1 jz_xloader.bin 0x80000000

clean:
	rm -fr *.o jz_xloader jz_xloader.bin jz_xloader.dump
