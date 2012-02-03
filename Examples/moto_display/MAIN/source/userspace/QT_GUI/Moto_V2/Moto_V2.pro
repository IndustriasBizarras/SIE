#-------------------------------------------------
#
# Project created by QtCreator 2011-12-11T19:00:10
#
#-------------------------------------------------

QT       += core gui

TARGET = Moto_V2
TEMPLATE = app


SOURCES += main.cpp\
        moto_v2.cpp \
        manometer.cpp \
        abstractmeter.cpp \
        widgetwithbackground.cpp \
        functions.cpp \
    qprog.cpp \
    jz_adc_peripheral.cpp \
    jz47xx_mmap.cpp \
    jz47xx_gpio.cpp \
    ADCw.cpp

HEADERS  += moto_v2.h \
        manometer.h \
        abstractmeter.h \
        widgetwithbackground.h \
        functions.h \
    qprog.h \
    jz_adc_peripheral.h \
    jz47xx_mmap.h \
    jz47xx_gpio.h \
    ADCw.h



FORMS    += moto_v2.ui

OTHER_FILES +=

RESOURCES += \
    img.qrc
