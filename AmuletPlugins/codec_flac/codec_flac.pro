#-------------------------------------------------
#
# Project created by QtCreator 2012-02-25T20:59:45
#
#-------------------------------------------------

QT       += core gui

TARGET = codec_flac
TEMPLATE = lib
CONFIG += plugin

SOURCES += codec_flac.cpp \
    codec_provider_flac.cpp \
    decoder_flac.cpp \
    encoder_flac.cpp \
    widget_flac.cpp

HEADERS += codec_flac.hpp \
    codec_provider_flac.hpp \
    decoder_flac.hpp \
    encoder_flac.hpp \
    widget_flac.hpp

DESTDIR = ../

INCLUDEPATH += $$PWD/../../AmuletCore
DEPENDPATH += $$PWD/../../AmuletCore

FORMS += \
    widget_flac.ui
