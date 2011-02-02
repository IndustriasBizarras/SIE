CC            = ![MIPS TOOLCHAIN]-gcc
CXX           = ![MIPS TOOLCHAIN]-g++
CFLAGS        = -pipe -O2 -Wall  
CXXFLAGS      = -pipe -O2 -Wall 
INCPATH       = -I.
LINK          = ![MIPS TOOLCHAIN]-g++
LFLAGS        = -Wl,-O1
LIBS          =  -L/usr/lib
AR            = ![MIPS TOOLCHAIN]-ar cqs
RANLIB        = ![MIPS TOOLCHAIN]-ranlib
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
MKDIR         = mkdir -p
TARGET        = ![SIE APP NAME]


OBJECTS       = ![MAIN OBJECT] \
		jz_adc_peripheral.o \
		jz47xx_gpio.o \
		jz47xx_mmap.o 

all: $(TARGET)

$(TARGET): $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

![MAIN OBJECT]: ![MAIN TEMPLATE] \
		jz_adc_peripheral.h \
		jz47xx_mmap.h \
		jz47xx_gpio.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

jz_adc_peripheral.o: jz_adc_peripheral.cpp jz_adc_peripheral.h \
		jz47xx_mmap.h \
		jz47xx_gpio.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o jz_adc_peripheral.o jz_adc_peripheral.cpp

jz47xx_gpio.o: jz47xx_gpio.cpp jz47xx_gpio.h \
		jz47xx_mmap.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o jz47xx_gpio.o jz47xx_gpio.cpp

jz47xx_mmap.o: jz47xx_mmap.cpp jz47xx_mmap.h \
		jz47xx_gpio.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o jz47xx_mmap.o jz47xx_mmap.cpp
