# This is an application
TEMPLATE=app

# The binary name
TARGET=noxchat

# This app uses Qtopia
CONFIG+=qtopia

# Build this app as a quicklauncher plugin
# You need to be using the QTOPIA_ADD_APPLICATION/QTOPIA_MAIN macros or this will not work!
#CONFIG+=quicklaunch

# Build this project into the singleexec binary
#CONFIG+=singleexec

#CONFIG+=stl

QT += network
QT += xml 

# Specify the languages that make lupdate should produce .ts files for
STRING_LANGUAGE=en_US
#LANGUAGES=en_US

# Package information (used for qbuild packages)
pkg [
    name=noxchat
    desc="IRC client"
    license=GPL
    version=0.1.0
    maintainer="ANT"
]

# These are the source files that get built to create the application
#FORMS=\
#    formbase.ui

HEADERS = irc_engine.h main_win.h tab_chat.h xml_config.h edit_message.h tab_manager.h win_joinchan.h list_user.h win_settings.h
SOURCES = irc_engine.cpp main.cpp main_win.cpp tab_chat.cpp xml_config.cpp edit_message.cpp tab_manager.cpp win_joinchan.cpp list_user.cpp win_settings.cpp

RESOURCES = icons.qrc

# SXE information
target [
    hint=sxe
    domain=untrusted
]

# Install some pictures.
pics [
    hint=pics
    files=icons/icon.png
    path=/pics/noxchat
]

image [
    hint=image
    files=NoChat.xml
    path=/etc/noxchat
]

# Install the launcher item. The metadata comes from the .desktop file
# and the path here.
desktop [
    hint=desktop
    files=noxchat.desktop
    path=/apps/Applications
]
