#-------------------------------------------------
#
# Project created by QtCreator 2012-02-17T20:35:43
#
#-------------------------------------------------

#QT       += core

#QT       -= gui

TARGET = amulet
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    codec_properties.cpp \
    converter_worker.cpp \
    converter_factory.cpp \
    converter_service.cpp \
    coder.cpp \
    decoder.cpp

HEADERS += \
    codec_properties.hpp \
    converter_worker.hpp \
    converter_factory.hpp \
    converter_service.hpp \
    coder.hpp \
    decoder.hpp
