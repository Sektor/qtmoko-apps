qtopia_project(qtopia app) # see buildsystem.html for more project keywords
TARGET=greensudoku
CONFIG+=qtopia_main
CONFIG+=no_quicklaunch

RESOURCES = sudoku.qrc

FORMS=gamedialog.ui \
      resultdialog.ui
HEADERS=gamedialog.h \
        gridkernel.h \
        mainwindow.h \
        resultdialog.h \
        grid.h \
        gridview.h \
        numberview.h \
		logitem.h \
		qqwing.h \
		gamewidget.h \
		sudokuboard.h
SOURCES=gamedialog.cpp \
        gridkernel.cpp \
        main.cpp \
        numberview.cpp \
        grid.cpp \
        gridview.cpp \
        mainwindow.cpp \
		resultdialog.cpp \
		logitem.cpp \
		qqwing.cpp \
		gamewidget.cpp \
		sudokuboard.cpp

desktop.files=greensudoku.desktop
desktop.path=/apps/Games
desktop.hint=desktop

pics.files=pics/*
pics.path=/pics/greensudoku
pics.hint=pics

help.source=help
help.files=html/greensudoku.html
help.hint=help

INSTALLS+=desktop pics help

pkg.name=greensudoku
pkg.desc=Sudoku Game
pkg.version=0.2
pkg.maintainer=Nicolas Arnaud-Cormos (nicolas@qtfr.org)
pkg.license=GPL
pkg.domain=window,games
