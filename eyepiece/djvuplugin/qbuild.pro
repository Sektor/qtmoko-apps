TEMPLATE=plugin
PLUGIN_FOR=qtopia
PLUGIN_TYPE=eyepiece

TARGET = djvuplugin

CONFIG += qtopia
CONFIG += release
CONFIG += no_pkg

HEADERS += djvuplugin.h
SOURCES += djvuplugin.cpp

INCLUDEPATH += $$shellQuote($$path(,project))/../application \
    $$MKSPEC.INCDIR

# Dependencies
LIBS += -L $$MKSPEC.LIBDIR -ldjvulibre -ljpeg

