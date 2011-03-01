EXTRA_CFLAGS += -Wall
OPENWRT_BASE  = /home/ari/sie/p/openwrt-xburst
KERNEL_SRC    = $(OPENWRT_BASE)/build_dir/linux-xburst_qi_lb60/linux-2.6.32.16/
CC            = $(OPENWRT_BASE)/staging_dir/toolchain-mipsel_gcc-4.3.3+cs_uClibc-0.9.32/usr/bin/mipsel-openwrt-linux-gcc
CROSS_COMPILE = $(OPENWRT_BASE)/staging_dir/toolchain-mipsel_gcc-4.3.3+cs_uClibc-0.9.32/usr/bin/mipsel-openwrt-linux-
NANO_IP = 192.168.254.101

obj-m += ps2_kb.o ps2_ms.o#hello.o memory.o digTest.o
all: driver #main

driver:
	make -C $(KERNEL_SRC) M=$(PWD)  ARCH=mips CROSS_COMPILE=$(CROSS_COMPILE) modules
clean:
	make -C $(KERNEL_SRC) M=$(PWD) ARCH=mips CROSS_COMPILE=$(CROSS_COMPILE) clean
	rm -f *.o Modules.symvers

cleanall:
	make -C $(KERNEL_SRC) M=$(PWD) ARCH=mips CROSS_COMPILE=$(CROSS_COMPILE) clean
	rm -f *.o  *.c~ Makefile~ main.o main Modules.symvers

upload: all 
	scp ps2_ms.ko root@$(NANO_IP):~/

main: main.o

PREPROCESS.c = $(CC) $(CFLAGS) $(TARGET_ARCH) -E -Wp,-C,-dD,-dI
%.pp : %.c FORCE
	$(PREPROCESS.c) $< > $@
