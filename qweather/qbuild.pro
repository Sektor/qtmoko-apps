# This is an application
TEMPLATE=app

# The binary name
TARGET=qweather

# This app uses Qtopia
CONFIG+=qtopia

QT += network \
    xml \
    gui

# Package information (used for qbuild packages)
pkg [
    name=qweather
    desc="Yahoo! Weather"
    license=GPL
    version=0.3.0
]

SOURCES += main.cpp \
    mainwindow.cpp \
    qweather.cpp \
    setupdlg.cpp \
    weatherinfowidget.cpp \
    gzip.cpp
HEADERS += mainwindow.h \
    qweather.h \
    setupdlg.h \
    weatherinfowidget.h \
    gzip.h

# Install the launcher item. The metadata comes from the .desktop file
# and the path here.
desktop [
    hint=desktop
    files=qweather.desktop
    path=/apps/Applications
]

# Install some pictures.
pics [
    hint=pics
    files=pics/*
    path=/pics/qweather
]

