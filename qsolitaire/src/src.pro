# Copyright (c) 2009 Nokia Corporation

INCLUDEPATH += inc
TEMPLATE = app
TARGET = qsolitaire
DEPENDPATH += .
INCLUDEPATH += .
DESTDIR = ../
VERSION = 1.3.0

symbian: { 
    SOURCES = qsolitaire.rss \
    qsolitaire_reg.rss
    }

symbian: { 
    HEADERS = qsolitaire.loc
}

SOURCES += main.cpp \
    TableauWidget.cpp \
    Card.cpp \
    SolitaireScene.cpp \
    CardDeck.cpp \
    GameLogic.cpp \
    Deck.cpp \
    Foundation.cpp \
    Stock.cpp \
    Waste.cpp \
    SolitaireView.cpp
    
HEADERS += TableauWidget.h \
    Card.h \
    SolitaireScene.h \
    CardDeck.h \
    GameLogic.h \
    Deck.h \
    Foundation.h \
    Stock.h \
    Waste.h \
    SolitaireView.h
    
RESOURCES = ../resources.qrc
QT += svg

# Symbian specific
symbian: { 
    TARGET.EPOCHEAPSIZE = 20000 \
        10000000
    TARGET.EPOCSTACKSIZE = 0x14000
    ICON = ../images/icon.svg
}

# Maemo specific
unix:!symbian { 
    # Variables
    isEmpty(PREFIX):PREFIX = /usr/local
    BINDIR = $$PREFIX/bin
    DATADIR = $$PREFIX/share
    DEFINES += DATADIR=\\\"$$DATADIR\\\" \
        PKGDATADIR=\\\"$$PKGDATADIR\\\"


    # MAKE INSTALL
    INSTALLS += target \
        desktop \
        iconxpm \
        icon26 \
        icon40 \
        icon64

    target.path = $$BINDIR
    desktop.path = $$DATADIR/applications/hildon
    desktop.files += qsolitaire.desktop

    iconxpm.path = $$DATADIR/pixmap
    iconxpm.files += ../images/icons/maemo/qsolitaire.xpm

    icon26.path = $$DATADIR/icons/hicolor/26x26/apps
    icon26.files += ../images/icons/26x26/qsolitaire.png

    icon40.path = $$DATADIR/icons/hicolor/40x40/apps
    icon40.files += ../images/icons/40x40/qsolitaire.png

    icon64.path = $$DATADIR/icons/hicolor/64x64/apps
    icon64.files += ../images/icons/64x64/qsolitaire.png
   
}
