CC       = mipsel-openwrt-linux-gcc
CXX      =  mipsel-openwrt-linux-g++
OPENWRT_BUILD_DIR = /home/cain/Embedded/ingenic/sakc/build/openwrt-xburst/staging_dir/target-mipsel_uClibc-0.9.30.1
INCLUDE  = -I. -I$(OPENWRT_BUILD_DIR)/usr/include/
WARNINGS = -Wcast-align -Wpacked -Wpadded -Wall 
CCFLAGS  = ${INCLUDE} ${DEBUG} ${WARNINGS} -std=c99 -fPIC
LDFLAGS  =
DEBUG    = -O3 -g0
TARGET   = candy

#luaavg:	
#	$(CXX) ${INCLUDE} -Wno-variadic-macros -fPIC luaavg.cc -llua -ldl -o luaavg

clean:
	rm -f luaavg
