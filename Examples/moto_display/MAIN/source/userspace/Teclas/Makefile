DESIGN = deb_user
EXTRA_CFLAGS += -Wall
CC            = ~/openwrt/trunk/staging_dir/toolchain-mipsel_gcc-4.5-linaro_uClibc-0.9.32/bin/mipsel-openwrt-linux-gcc
OPENWRT_BASE  = ~/openwrt/trunk/
KERNEL_SRC    = $(OPENWRT_BASE)/build_dir/linux-xburst_qi_lb60/linux-2.6.37.6/
CROSS_COMPILE = ~/openwrt/trunk/staging_dir/toolchain-mipsel_gcc-4.5-linaro_uClibc-0.9.32/bin/mipsel-openwrt-linux-

obj-m +=  deb.o 
all: $(DESIGN)

clean:
	make -C $(KERNEL_SRC) M=$(PWD) ARCH=mips CROSS_COMPILE=$(CROSS_COMPILE) clean
	rm -rf *.o main.o main deb.ko Modules.symvers $(DESIGN)

main: main.o
PREPROCESS.c = $(CC) $(CFLAGS) $(TARGET_ARCH) -E -Wp,-C,-dD,-dI
%.pp : %.c FORCE
	$(PREPROCESS.c) $< > $@
upload: $(DESIGN)
	scp $(DESIGN) root@192.168.200.1:~/pruebas


