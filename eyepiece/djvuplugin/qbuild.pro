TEMPLATE=plugin
PLUGIN_FOR=qtopia
PLUGIN_TYPE=eyepiece

TARGET = djvuplugin

CONFIG += qtopia
CONFIG += release
CONFIG += no_pkg

HEADERS += djvuplugin.h
SOURCES += djvuplugin.cpp

INCLUDEPATH += ../application

# Dependencies
LIBS += -ldjvulibre

