# Copyright (c) 2009 Nokia Corporation

TEMPLATE=app

# The binary name
TARGET=qsolitaire

# This app uses Qtopia
CONFIG+=qtopia

SOURCES += main_qtopia.cpp \
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

pkg [
    name=qsolitaire
    desc="qsolitaire"
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
    files=qsolitaire.desktop
    path=/apps/Games
]

pics [
    hint=pics
    files=../images/icons/60x60/*
    path=/pics/qsolitaire
]
