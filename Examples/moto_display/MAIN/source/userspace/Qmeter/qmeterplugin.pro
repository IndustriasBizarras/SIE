CONFIG      += designer plugin release
TARGET      = $$qtLibraryTarget($$TARGET)
TEMPLATE    = lib
QTDIR_build:DESTDIR     = $$QT_BUILD_TREE/plugins/designer

VERSION = 0.5.1

HEADERS     += qmeter.h \
              qmeterplugin.h \
              qmetertaskmenu.h \
              properties_dialog.h             
SOURCES     += qmeter.cpp \
              qmeterplugin.cpp \
              qmetertaskmenu.cpp \
              properties_dialog.cpp \           
              qmeterdrawfunctions.cpp

FORMS        += properties.ui

RESOURCES    = qmeter.qrc
# install
target.path = $$[QT_INSTALL_PLUGINS]/designer
sources.files = $$SOURCES $$HEADERS *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/designer/qmeterplugin
INSTALLS += target sources
