# Spartan3 JTAG programmer and other utilities

# Copyright (C) 2004 Andrew Rogers

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 


GXX=mipsel-openwrt-linux-g++
GCC=mipsel-openwrt-linux-gcc
LIBS=-lstdc++

all:	 xc3sprog
#debug bitparse detectchain xc3sprog

debug: debug.o iobase.o sakcXCProgrammer.o iodebug.o
	${GXX}  -Wall ${LIBS} $^ -o $@

bitparse: bitparse.o bitfile.o
	${GXX} -Wall ${LIBS} $^ -o $@

detectchain: detectchain.o jtag.o iobase.o sakcXCProgrammer.o iodebug.o devicedb.o
	${GXX}  -Wall ${LIBS} $^ -o $@

xc3sprog: xc3sprog.o jtag.o iobase.o sakcXCProgrammer.o iodebug.o bitfile.o devicedb.o progalgxcf.o progalgxc3s.o jz47xx_gpio.o
	${GXX}  -Wall ${LIBS} $^ -o $@

debug.o: debug.cpp iobase.h sakcXCProgrammer.h iodebug.h
	${GXX}  -Wall -c $< -o $@

bitparse.o: bitparse.cpp bitfile.h
	${GXX}  -Wall -c $< -o $@

detectchain.o: detectchain.cpp iobase.h sakcXCProgrammer.h jtag.h iodebug.h devicedb.h
	${GXX}  -Wall -c $< -o $@

xc3sprog.o: xc3sprog.cpp iobase.h sakcXCProgrammer.h jtag.h iodebug.h bitfile.h devicedb.h progalgxcf.h progalgxc3s.h
	${GXX}  -Wall -c $< -o $@

iobase.o: iobase.cpp iobase.h
	${GXX} -c $< -o $@

iodebug.o: iodebug.cpp iodebug.h iobase.h
	${GXX} -c $< -o $@

sakcXCProgrammer.o: sakcXCProgrammer.cpp sakcXCProgrammer.h iobase.h
	${GXX} -c $< -o $@ 

bitfile.o: bitfile.cpp bitfile.h
	${GXX} -c $< -o $@

jtag.o: jtag.cpp jtag.h
	${GXX} -c $< -o $@

devicedb.o: devicedb.cpp devicedb.h
	${GXX} -c $< -o $@

progalgxcf.o: progalgxcf.cpp progalgxcf.h iobase.h jtag.h bitfile.h
	${GXX} -c $< -o $@

progalgxc3s.o: progalgxc3s.cpp progalgxc3s.h iobase.h jtag.h bitfile.h
	${GXX} -c $< -o $@

jz47xx_gpio.o: jz47xx_gpio.c jz47xx_gpio.h
	${GCC} -c $< -o $@

clean:
	rm -f debug.o iobase.o sakcXCProgrammer.o iodebug.o bitfile.o jtag.o xc3sprog.o 
	rm -f devicedb.o bitparse.o detectchain.o progalgxcf.o progalgxc3s.o
	rm -f debug bitparse detectchain xc3sprog jz47xx_gpio.o *~
