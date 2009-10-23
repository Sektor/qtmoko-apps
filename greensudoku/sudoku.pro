TEMPLATE = app
CONFIG += debug \
          warn_on \
	  thread \
          qt
TARGET = bin/sudoku

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
QT += core \
gui

RESOURCES = sudoku.qrc

