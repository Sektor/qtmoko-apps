# This is an application
TEMPLATE=app

# The binary name
TARGET=keyboard-skin-silver

CONFIG+=qtopia

# Package information (used for qbuild packages)
pkg [
    name=keyboard-skin-silver
    desc="Skin for FingerKeyboard. Works with QtMoko V11 or newer. Restart of the system is required after installation."
    license=GPL
    version=1.0.0-1
    maintainer="ANT"
]

SOURCES=\
    main.cpp

layout [
    hint=image
    files=skin.conf
    path=/etc/fingerkeyboard
]

pics [
    hint=pics
    files=pics/*
    path=/pics/fingerkeyboard/skins/silver
]

desktop [
    hint=desktop
    files=keyboard-skin-silver.desktop
    path=/apps/Settings
]

