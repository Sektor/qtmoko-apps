# This is an application
TEMPLATE=app

# The binary name
TARGET=qgt

# This app uses Qtopia
CONFIG+=qtopia

AVAILABLE_LANGUAGES = ru_RU en_US
STRING_LANGUAGE = en_US
LANGUAGES = ru_RU en_US

# Package information (used for qbuild packages)
pkg [
    name=qgoogletranslate
    desc="Google Translate service client"
    license=GPL
    version=0.1.3-r1
    maintainer="ANT"
]

FORMS = ui/mainwindow.ui \
    ui/editorwidget.ui \
    ui/configdialog.ui
HEADERS = src/mainwindow.h \
    src/ceditorwidget.h \
    src/cconfigdialog.h \
    version.h
SOURCES = src/mainwindow.cpp \
    src/main.cpp \
    src/ceditorwidget.cpp \
    src/cconfigdialog.cpp
RESOURCES += rc/icons.qrc

# SXE information
target [
    hint=sxe
    domain=untrusted
]

# Install the launcher item. The metadata comes from the .desktop file
# and the path here.
desktop [
    hint=desktop
    files=icons/qgt.desktop
    path=/apps/Applications
]

icon [
    hint=pics
    files=icons/icon.png
    path=/pics/qgt
]
