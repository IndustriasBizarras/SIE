TOOLCHAIN_BASE= ![MIPS TOOLCHAIN]/![MIPS TOOLCHAIN BASE]
CC            = ${TOOLCHAIN_BASE}-gcc
CXX           = ${TOOLCHAIN_BASE}-g++
INCPATH       = -I.
CFLAGS        = ${INCPATH} -pipe -O2 -mips32 -mtune=mips32 -Wall  
CXXFLAGS      = ${INCPATH} -pipe -O2 -mips32 -mtune=mips32 -Wall 
LINK          = ${TOOLCHAIN_BASE}-g++
LFLAGS        = -Wl,-O1
LIBS          = -lstdc++
AR            = ${TOOLCHAIN_BASE}-ar cqs
RANLIB        = ${TOOLCHAIN_BASE}-ranlib
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
MKDIR         = mkdir -p
TARGET        = ![SIE APP NAME]


OBJECTS       = ![MAIN OBJECT] \
		jz_adc_peripheral.o \
		jz_fpga_init.o \
		jz47xx_gpio.o \
		jz47xx_mmap.o \
		fbutils.o
		
#BUILD RULES
all: $(TARGET)

$(TARGET): $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)
	
fbutils.o:  fbutils.c fbutils.h
	$(CC) $(CFLAGS) $(INCPATH) -c $< -o $@

jz47xx_gpio.o: jz47xx_gpio.cpp \
		jz47xx_mmap.h
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $< -o $@

jz47xx_mmap.o: jz47xx_mmap.cpp \
		jz47xx_gpio.h
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $< -o $@

jz_adc_peripheral.o: jz_adc_peripheral.cpp \
		jz_fpga_init.h \
		jz47xx_gpio.h \
		jz47xx_mmap.h
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $< -o $@

jz_fpga_init.o: jz_fpga_init.cpp \
		jz47xx_gpio.h \
		jz47xx_mmap.h
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $< -o $@

![MAIN OBJECT]: ![MAIN TEMPLATE] \
		jz_adc_peripheral.h \
		jz_fpga_init.h
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $< -o $@
	
	
clean: 
	$(DEL_FILE) *.o $(TARGET)
	
