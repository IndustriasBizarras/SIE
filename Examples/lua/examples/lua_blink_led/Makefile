CC        = mipsel-openwrt-linux-gcc
CXX       = mipsel-openwrt-linux-g++
OPENWRT_BUILD_DIR = /home/cain/Embedded/ingenic/sakc/build/openwrt-xburst/staging_dir/target-mipsel_uClibc-0.9.30.1
INCLUDE   = -I. -I$(OPENWRT_BUILD_DIR)/usr/include/
WARNINGS  = -Wcast-align -Wpacked -Wpadded -Wall 
CCFLAGS   = ${INCLUDE} ${DEBUG} ${WARNINGS} -std=c99 -fPIC
LDFLAGS   = -L$(OPENWRT_BUILD_DIR)/usr/lib -llua -ldl
DEBUG     = -O3 -g0
NANO_PATH = root@192.168.254.101:
TARGET    = gpio

COMMON_SOURCES = jz47xx_gpio.c jz47xx_mmap.c sram_gpio_wrap.c
COMMON_OBJECTS = $(COMMON_SOURCES:.c=.o)


$(TARGET): $(COMMON_OBJECTS)
	$(CC)  $(CCFLAGS) $(LDFLAGS) -shared  $(COMMON_OBJECTS) -o  $(TARGET).so

.c.o:
	$(CC) -c $(CCFLAGS) $< -o $@

upload: $(TARGET)
	scp $(TARGET).so test_gpio.lua $(NANO_PATH)
	
clean:
	rm -f *.o $(TARGET).so
