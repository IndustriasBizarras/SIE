#############################################################################
# Makefile for building: Moto_V2
# Generated by qmake (2.01a) (Qt 4.7.2) on: Thu Jan 26 00:56:52 2012
# Project:  ../Moto_V2/Moto_V2.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ QMLJSDEBUGGER_PATH=/usr/share/qtcreator/qml/qmljsdebugger -o Makefile ../Moto_V2/Moto_V2.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I../Moto_V2 -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I. -I../Moto_V2 -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ../Moto_V2/main.cpp \
		../Moto_V2/moto_v2.cpp \
		../Moto_V2/manometer.cpp \
		../Moto_V2/abstractmeter.cpp \
		../Moto_V2/widgetwithbackground.cpp \
		../Moto_V2/functions.cpp \
		../Moto_V2/qprog.cpp \
		../Moto_V2/jz_adc_peripheral.cpp \
		../Moto_V2/jz47xx_mmap.cpp \
		../Moto_V2/jz47xx_gpio.cpp \
		../Moto_V2/ADCw.cpp moc_moto_v2.cpp \
		moc_manometer.cpp \
		moc_abstractmeter.cpp \
		moc_widgetwithbackground.cpp \
		moc_qprog.cpp \
		qrc_img.cpp
OBJECTS       = main.o \
		moto_v2.o \
		manometer.o \
		abstractmeter.o \
		widgetwithbackground.o \
		functions.o \
		qprog.o \
		jz_adc_peripheral.o \
		jz47xx_mmap.o \
		jz47xx_gpio.o \
		ADCw.o \
		moc_moto_v2.o \
		moc_manometer.o \
		moc_abstractmeter.o \
		moc_widgetwithbackground.o \
		moc_qprog.o \
		qrc_img.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		../Moto_V2/Moto_V2.pro
QMAKE_TARGET  = Moto_V2
DESTDIR       = 
TARGET        = Moto_V2

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_moto_v2.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: ../Moto_V2/Moto_V2.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ QMLJSDEBUGGER_PATH=/usr/share/qtcreator/qml/qmljsdebugger -o Makefile ../Moto_V2/Moto_V2.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ QMLJSDEBUGGER_PATH=/usr/share/qtcreator/qml/qmljsdebugger -o Makefile ../Moto_V2/Moto_V2.pro

dist: 
	@$(CHK_DIR_EXISTS) ../Moto_V2/.tmp/Moto_V21.0.0 || $(MKDIR) ../Moto_V2/.tmp/Moto_V21.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) ../Moto_V2/.tmp/Moto_V21.0.0/ && $(COPY_FILE) --parents ../Moto_V2/moto_v2.h ../Moto_V2/manometer.h ../Moto_V2/abstractmeter.h ../Moto_V2/widgetwithbackground.h ../Moto_V2/functions.h ../Moto_V2/qprog.h ../Moto_V2/jz_adc_peripheral.h ../Moto_V2/jz47xx_mmap.h ../Moto_V2/jz47xx_gpio.h ../Moto_V2/ADCw.h ../Moto_V2/.tmp/Moto_V21.0.0/ && $(COPY_FILE) --parents ../Moto_V2/img.qrc ../Moto_V2/.tmp/Moto_V21.0.0/ && $(COPY_FILE) --parents ../Moto_V2/main.cpp ../Moto_V2/moto_v2.cpp ../Moto_V2/manometer.cpp ../Moto_V2/abstractmeter.cpp ../Moto_V2/widgetwithbackground.cpp ../Moto_V2/functions.cpp ../Moto_V2/qprog.cpp ../Moto_V2/jz_adc_peripheral.cpp ../Moto_V2/jz47xx_mmap.cpp ../Moto_V2/jz47xx_gpio.cpp ../Moto_V2/ADCw.cpp ../Moto_V2/.tmp/Moto_V21.0.0/ && $(COPY_FILE) --parents ../Moto_V2/moto_v2.ui ../Moto_V2/.tmp/Moto_V21.0.0/ && (cd `dirname ../Moto_V2/.tmp/Moto_V21.0.0` && $(TAR) Moto_V21.0.0.tar Moto_V21.0.0 && $(COMPRESS) Moto_V21.0.0.tar) && $(MOVE) `dirname ../Moto_V2/.tmp/Moto_V21.0.0`/Moto_V21.0.0.tar.gz . && $(DEL_FILE) -r ../Moto_V2/.tmp/Moto_V21.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_moto_v2.cpp moc_manometer.cpp moc_abstractmeter.cpp moc_widgetwithbackground.cpp moc_qprog.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_moto_v2.cpp moc_manometer.cpp moc_abstractmeter.cpp moc_widgetwithbackground.cpp moc_qprog.cpp
moc_moto_v2.cpp: ../Moto_V2/ADCw.h \
		../Moto_V2/jz_adc_peripheral.h \
		../Moto_V2/jz47xx_mmap.h \
		../Moto_V2/jz47xx_gpio.h \
		../Moto_V2/moto_v2.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ../Moto_V2/moto_v2.h -o moc_moto_v2.cpp

moc_manometer.cpp: ../Moto_V2/analogwidgets/abstractmeter.h \
		../Moto_V2/widgetwithbackground.h \
		../Moto_V2/manometer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ../Moto_V2/manometer.h -o moc_manometer.cpp

moc_abstractmeter.cpp: ../Moto_V2/widgetwithbackground.h \
		../Moto_V2/abstractmeter.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ../Moto_V2/abstractmeter.h -o moc_abstractmeter.cpp

moc_widgetwithbackground.cpp: ../Moto_V2/widgetwithbackground.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ../Moto_V2/widgetwithbackground.h -o moc_widgetwithbackground.cpp

moc_qprog.cpp: ../Moto_V2/qprog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ../Moto_V2/qprog.h -o moc_qprog.cpp

compiler_rcc_make_all: qrc_img.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_img.cpp
qrc_img.cpp: ../Moto_V2/img.qrc \
		../Moto_V2/carbon.png \
		../Moto_V2/left_off.png \
		../Moto_V2/right_on.png \
		../Moto_V2/right_off.png \
		../Moto_V2/left_on.png
	/usr/bin/rcc -name img ../Moto_V2/img.qrc -o qrc_img.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_moto_v2.h
compiler_uic_clean:
	-$(DEL_FILE) ui_moto_v2.h
ui_moto_v2.h: ../Moto_V2/moto_v2.ui \
		../Moto_V2/analogwidgets/manometer.h \
		../Moto_V2/qprog.h \
		../Moto_V2/analogwidgets/abstractmeter.h \
		../Moto_V2/widgetwithbackground.h
	/usr/bin/uic-qt4 ../Moto_V2/moto_v2.ui -o ui_moto_v2.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: ../Moto_V2/main.cpp ../Moto_V2/moto_v2.h \
		../Moto_V2/ADCw.h \
		../Moto_V2/jz_adc_peripheral.h \
		../Moto_V2/jz47xx_mmap.h \
		../Moto_V2/jz47xx_gpio.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o ../Moto_V2/main.cpp

moto_v2.o: ../Moto_V2/moto_v2.cpp ../Moto_V2/moto_v2.h \
		../Moto_V2/ADCw.h \
		../Moto_V2/jz_adc_peripheral.h \
		../Moto_V2/jz47xx_mmap.h \
		../Moto_V2/jz47xx_gpio.h \
		../Moto_V2/ui_moto_v2.h \
		../Moto_V2/analogwidgets/manometer.h \
		../Moto_V2/analogwidgets/abstractmeter.h \
		../Moto_V2/widgetwithbackground.h \
		../Moto_V2/qprog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moto_v2.o ../Moto_V2/moto_v2.cpp

manometer.o: ../Moto_V2/manometer.cpp ../Moto_V2/manometer.h \
		../Moto_V2/analogwidgets/abstractmeter.h \
		../Moto_V2/widgetwithbackground.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o manometer.o ../Moto_V2/manometer.cpp

abstractmeter.o: ../Moto_V2/abstractmeter.cpp ../Moto_V2/analogwidgets/abstractmeter.h \
		../Moto_V2/widgetwithbackground.h \
		../Moto_V2/functions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o abstractmeter.o ../Moto_V2/abstractmeter.cpp

widgetwithbackground.o: ../Moto_V2/widgetwithbackground.cpp ../Moto_V2/widgetwithbackground.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o widgetwithbackground.o ../Moto_V2/widgetwithbackground.cpp

functions.o: ../Moto_V2/functions.cpp ../Moto_V2/functions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o functions.o ../Moto_V2/functions.cpp

qprog.o: ../Moto_V2/qprog.cpp ../Moto_V2/qprog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qprog.o ../Moto_V2/qprog.cpp

jz_adc_peripheral.o: ../Moto_V2/jz_adc_peripheral.cpp ../Moto_V2/jz_adc_peripheral.h \
		../Moto_V2/jz47xx_mmap.h \
		../Moto_V2/jz47xx_gpio.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o jz_adc_peripheral.o ../Moto_V2/jz_adc_peripheral.cpp

jz47xx_mmap.o: ../Moto_V2/jz47xx_mmap.cpp ../Moto_V2/jz47xx_mmap.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o jz47xx_mmap.o ../Moto_V2/jz47xx_mmap.cpp

jz47xx_gpio.o: ../Moto_V2/jz47xx_gpio.cpp ../Moto_V2/jz47xx_gpio.h \
		../Moto_V2/jz47xx_mmap.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o jz47xx_gpio.o ../Moto_V2/jz47xx_gpio.cpp

ADCw.o: ../Moto_V2/ADCw.cpp ../Moto_V2/ADCw.h \
		../Moto_V2/jz_adc_peripheral.h \
		../Moto_V2/jz47xx_mmap.h \
		../Moto_V2/jz47xx_gpio.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ADCw.o ../Moto_V2/ADCw.cpp

moc_moto_v2.o: moc_moto_v2.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_moto_v2.o moc_moto_v2.cpp

moc_manometer.o: moc_manometer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_manometer.o moc_manometer.cpp

moc_abstractmeter.o: moc_abstractmeter.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_abstractmeter.o moc_abstractmeter.cpp

moc_widgetwithbackground.o: moc_widgetwithbackground.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_widgetwithbackground.o moc_widgetwithbackground.cpp

moc_qprog.o: moc_qprog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qprog.o moc_qprog.cpp

qrc_img.o: qrc_img.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_img.o qrc_img.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

