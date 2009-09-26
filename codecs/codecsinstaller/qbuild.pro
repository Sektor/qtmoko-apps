# This is an application
TEMPLATE=app

# The binary name
TARGET=codecsinstaller

# This app uses Qtopia
CONFIG+=qtopia
 
SOURCES += main.cpp \
           codecsinstaller.cpp

HEADERS += codecsinstaller.h

RESOURCES += resources.qrc

PRERUN_RULES=copy_libmad copy_libmad_plugin
POSTRUN_RULES=rm_libmad rm_libmad_plugin

copy_libmad [
    TYPE=RULE
    outputFiles=libmad.so
    commands="cp $$shellQuote($$path(,generated)/../../../sdk/lib/libmad.so) $$shellQuote($$path(,project))"
]

rm_libmad [
    TYPE=RULE
    commands="rm -f $$shellQuote($$path(,project)/libmad.so)"
]

copy_libmad_plugin [
    TYPE=RULE
    outputFiles=libmadplugin.so
    commands="cp $$shellQuote($$path(,generated)/../../../src/3rdparty/plugins/codecs/libmad/libmadplugin.so) $$shellQuote($$path(,project))"
]

rm_libmad_plugin [
    TYPE=RULE
    commands="rm -f $$shellQuote($$path(,project)/libmadplugin.so)"
]

pkg [
    name=codecs
    desc="codecs"
    version=$$QTOPIA_VERSION
    license=$$QTOPIA_LICENSE
    maintainer=$$QTOPIA_MAINTAINER
]

target [
    hint=sxe
    domain=trusted
]

desktop [
    hint=desktop
    files=codecsinstaller.desktop
    path=/apps/Applications
]

pics [
    hint=pics
    files=pics/*
    path=/pics/codecsinstaller
]
