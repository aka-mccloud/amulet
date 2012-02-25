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
    codec_provider.cpp \
    encoder.cpp

HEADERS += codec_lame.hpp \
    codec_provider.hpp \
    encoder.hpp

DESTDIR = ../

INCLUDEPATH += $$PWD/../../AmuletCore
DEPENDPATH += $$PWD/../../AmuletCore
