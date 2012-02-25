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
    codec_provider.cpp \
    decoder.cpp

HEADERS += codec_flac.hpp \
    codec_provider.hpp \
    decoder.hpp

DESTDIR = ../

INCLUDEPATH += $$PWD/../../AmuletCore
DEPENDPATH += $$PWD/../../AmuletCore
