CC  = ~/openwrt/trunk/staging_dir/toolchain-mipsel_gcc-4.5-linaro_uClibc-0.9.32/bin/mipsel-openwrt-linux-gcc

all: TestADC

DEBUG = -O3 -g0

COMMON_SOURCES =  jz47xx_gpio.cpp jz47xx_mmap.cpp 

H_SOURCES = jz47xx_gpio.h jz47xx_mmap.h

INCLUDE = -I.

WARNINGS= -Wcast-align -Wpacked -Wpadded -Wall

CCFLAGS = ${INCLUDE} ${DEBUG} ${WARNINGS} 

LDFLAGS =

COMMON_OBJECTS = $(COMMON_SOURCES:.c=.o)

NANO_IP = 192.168.254.101

TestADC: $(COMMON_OBJECTS)
	$(CC)  $(LDFLAGS) $(COMMON_OBJECTS) TestADC.cpp -o TestADC

.c.o:
	$(CC) -c $(CCFLAGS) $< -o $@

upload: jz_init_sram jz_test_gpio 
	scp jz_test_gpio jz_init_sram root@$(NANO_IP):

clean: 
	rm -f *.o jz_init_sram jz_test_gpio enable_rx TestADC ${EXEC} *~ enable_irq

indent:
	indent -bad -bap -nbc -bl -nce -i2 --no-tabs --line-length120 $(COMMON_SOURCES) $(H_SOURCES)
