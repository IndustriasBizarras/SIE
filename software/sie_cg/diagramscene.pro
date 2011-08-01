HEADERS = mainwindow.h \
    diagramitem.h \
    diagramscene.h \
    arrow.h \
    diagramtextitem.h \
    lineitem.h \
    codedialog.h \
    codedialog.h \
    codedialog.h \
    optionsdialog.h \
    callapp.h
SOURCES = mainwindow.cpp \
    diagramitem.cpp \
    main.cpp \
    arrow.cpp \
    diagramtextitem.cpp \
    diagramscene.cpp \
    lineitem.cpp \
    codedialog.cpp \
    optionsdialog.cpp \
    callapp.cpp
RESOURCES = diagramscene.qrc
TARGET = diagrameditor

# install
target.path = $$[QT_INSTALL_EXAMPLES]/graphicsview/diagramscene
sources.files = $$SOURCES \
    $$HEADERS \
    $$RESOURCES \
    $$FORMS \
    diagramscene.pro \
    images
sources.path = $$[QT_INSTALL_EXAMPLES]/graphicsview/diagramscene
INSTALLS += target \
    sources
symbian:include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
QT += xml \
    svg \
    network
FORMS += librarydialog.ui \
    codedialog.ui \
    optionsdialog.ui

