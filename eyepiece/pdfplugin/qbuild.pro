TEMPLATE=plugin
PLUGIN_FOR=qtopia
PLUGIN_TYPE=eyepiece

TARGET = pdfplugin

CONFIG += qtopia
CONFIG += release
CONFIG += no_pkg

HEADERS += pdfplugin.h
SOURCES += pdfplugin.cpp

INCLUDEPATH += $$shellQuote($$path(,project))/../application

LIBS += -L $$MKSPEC.LIBDIR -ljpeg -lfontconfig -lfreetype -lexpat

# Dependencies
MODULES += poppler
