TEMPLATE=app

TARGET = eyepiece

CONFIG += qtopia
CONFIG += no_quicklaunch
CONFIG += no_singleexec
CONFIG += release
#CONFIG += debug

AVAILABLE_LANGUAGES = en_US
LANGUAGES = $$AVAILABLE_LANGUAGES

HEADERS = \
  eyepiece.h \
  document.h \
  eyedrawwidget.h \
  eyeosd.h \
  installer.h \
  accelerometers.h
SOURCES = \
  main.cpp \
  eyepiece.cpp \
  eyedrawwidget.cpp \
  eyeosd.cpp \
  installer.cpp \
  accelerometers.cpp
FORMS += eyepieceui.ui
RESOURCES += res/eyepiece.qrc

pkg [
  name = eyepiece
  desc = "DjVu/PDF viewer for Qt Extended"
  version = 0.2.0-alpha-r1
  maintainer = ANT
  license = GPL
]

# SXE information
target [
    hint=sxe
    domain=untrusted
]

desktop [
  hint = desktop
  files = eyepiece.desktop
  path = /apps/Applications
]

pics [
  hint = pics
  files = pics/*
  path = /pics/eyepiece
]

#help [
#  hint = help
#  source = help
#  files = eyepiece.html
#]

pdfplugin [
  hint=image generated
  files=../pdfplugin/libpdfplugin.so
  path=/plugins/eyepiece
]

djvuplugin [
  hint=image generated
  files=../djvuplugin/libdjvuplugin.so
  path=/plugins/eyepiece
]

