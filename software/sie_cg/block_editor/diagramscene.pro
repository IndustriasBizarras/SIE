HEADERS = mainwindow.h \
    diagramscene.h \
    arrow.h \
    diagramtextitem.h \
    lineitem.h
SOURCES = mainwindow.cpp \
    main.cpp \
    arrow.cpp \
    diagramtextitem.cpp \
    diagramscene.cpp \
    lineitem.cpp
RESOURCES = diagramscene.qrc

TARGET = blockeditor

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
