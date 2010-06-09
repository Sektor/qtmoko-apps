# -------------------------------------------------
# Project created by QtCreator 2008-12-16T00:05:30
# -------------------------------------------------
qtopia_project(qtopia app)
CONFIG+=qtopia_main no_quicklaunch

QT += network \
    xml \
    gui
TARGET = qweather
TEMPLATE = app
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

desktop.files = weather.desktop
desktop.path= /apps/Application
desktop.hint=desktop

INSTALLS+= desktop

pics.files=pics/*
pics.path=/pics/qweather
pics.hint=pics

INSTALLS+= pics

pkg.name=yweather
pkg.desk= Yahoo!Weather
pkg.version=0.3.0
pkg.license=GPL
pkg.domain=trusted
