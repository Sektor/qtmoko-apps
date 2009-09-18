# This is an application
TEMPLATE=app

# The binary name
TARGET=keyboard-russian-abc

CONFIG+=qtopia

# Package information (used for qbuild packages)
pkg [
    name=keyboard-russian-abc
    desc="Russian Alphabetical layout for FingerKeyboard. Works with QtMoko V10 or newer. Restart of the system is required after installation."
    license=GPL
    version=1.0.0-1
    maintainer="ANT"
]

SOURCES=\
    main.cpp

layout [
    hint=image
    files=extralayout.conf
    path=/etc/fingerkeyboard
]

desktop [
    hint=desktop
    files=keyboard-russian-abc.desktop
    path=/apps/Settings
]

