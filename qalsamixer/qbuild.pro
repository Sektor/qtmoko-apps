# This is an application
TEMPLATE=app

# The binary name
TARGET=qalsamixer

# This app uses Qtopia
CONFIG+=qtopia

HEADERS  = mixertoggle.h mixerslider.h qalsamixer.h
SOURCES  = mixertoggle.cpp mixerslider.cpp qalsamixer.cpp main.cpp
LIBS    += -lasound

# Package information
pkg [
    name=qalsamixer
    desc="Alsa mixer"
    version=1.0.0-1
    maintainer="QtMoko-Apps Team"
]

desktop [
    hint=desktop
    files=qalsamixer.desktop
    path=/apps/Applications
]

pics [
    hint=pics
    files=qalsamixer.png
    path=/pics/qalsamixer
]

