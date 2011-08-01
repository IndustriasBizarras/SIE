CC       = mipsel-openwrt-linux-gcc
CXX      =  mipsel-openwrt-linux-g++
OPENWRT_BUILD_DIR = /home/cain/Embedded/ingenic/sakc/build/openwrt-xburst/staging_dir/target-mipsel_uClibc-0.9.30.1
INCLUDE  = -I. -I$(OPENWRT_BUILD_DIR)/usr/include/
WARNINGS = -Wcast-align -Wpacked -Wpadded -Wall 
CCFLAGS  = ${INCLUDE} ${DEBUG} ${WARNINGS} -std=c99 -fPIC
LDFLAGS  =
DEBUG    = -O3 -g0
NANO_PATH = root@192.168.254.101:
TARGET   = fromlua

$(TARGET): $(TARGET)
	$(CC)  $(CCFLAGS) -o $(TARGET).so -shared $(TARGET).c

.c.o:
	$(CC) -c $(CCFLAGS) -o $@

upload: $(TARGET)
	scp $(TARGET).so top1.lua $(NANO_PATH)


clean:
	rm -f *.o $(TARGET).so
