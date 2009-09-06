TEMPLATE=plugin
PLUGIN_FOR=qtopia
PLUGIN_TYPE=eyepiece

TARGET = pdfplugin

CONFIG += qtopia
CONFIG += release
CONFIG += no_pkg

HEADERS += pdfplugin.h
SOURCES += pdfplugin.cpp

INCLUDEPATH += ../application
#INCLUDEPATH += /opt/toolchains/arm920t-eabi/arm-angstrom-linux-gnueabi/include/poppler/qt4

# Dependencies
LIBS += -lpoppler-qt4

