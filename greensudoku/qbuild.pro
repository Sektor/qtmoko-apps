# This is an application
TEMPLATE=app

# The binary name
TARGET=greensudoku

# This app uses Qtopia
CONFIG+=qtopia

DEFINES+=QTOPIA_PHONE

FORMS += gamedialog.ui \
         resultdialog.ui

SOURCES += main.cpp \
           grid.cpp \
           gridkernel.cpp \
           gridview.cpp \
           mainwindow.cpp \
           numberview.cpp \
           gamedialog.cpp \
           resultdialog.cpp \
           logitem.cpp \
           qqwing.cpp \
           gamewidget.cpp \
           sudokuboard.cpp

HEADERS += grid.h \
           gridkernel.h \
           gridview.h \
           mainwindow.h \
           numberview.h \
           gamedialog.h \
           resultdialog.h \
           numberview.h \
           logitem.h \
           qqwing.h \
           gamewidget.h \
           sudokuboard.h

RESOURCES = sudoku.qrc

pkg [
    name=greensudoku
    desc="greensudoku"
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
    files=greensudoku.desktop
    path=/apps/Games
]

pics [
    hint=pics
    files=pics/*
    path=/pics/greensudoku
]
