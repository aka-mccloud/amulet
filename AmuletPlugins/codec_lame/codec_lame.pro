#-------------------------------------------------
#
# Project created by QtCreator 2012-02-25T21:00:26
#
#-------------------------------------------------

QT       += core gui

TARGET = codec_lame
TEMPLATE = lib
CONFIG += plugin

SOURCES += codec_lame.cpp \
    widget_lame.cpp \
    encoder_lame.cpp \
    codec_provider_lame.cpp

HEADERS += codec_lame.hpp \
    encoder_lame.hpp \
    widget_lame.hpp \
    codec_provider_lame.hpp

DESTDIR = ../

INCLUDEPATH += $$PWD/../../AmuletCore
DEPENDPATH += $$PWD/../../AmuletCore

FORMS += \
    widget_lame.ui
