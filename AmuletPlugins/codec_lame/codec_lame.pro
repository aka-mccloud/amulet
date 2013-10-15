#-------------------------------------------------
#
# Project created by QtCreator 2013-10-09T09:38:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = codec_lame
TEMPLATE = lib

DEFINES += CODEC_LAME_LIBRARY

SOURCES += codec_lame.cpp \
    widget_lame.cpp \
    encoder_lame.cpp \
    decoder_lame.cpp \
    codec_provider_lame.cpp

HEADERS += \
    widget_lame.hpp \
    encoder_lame.hpp \
    decoder_lame.hpp \
    codec_provider_lame.hpp \
    codec_lame.hpp

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/share/amulet/plugins
    } else {
        target.path = /usr/share/amulet/plugins
    }
    INSTALLS += target
}

FORMS += \
    widget_lame.ui


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../AmuletCore/release/ -lAmuletCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../AmuletCore/debug/ -lAmuletCore
else:unix: LIBS += -L$$OUT_PWD/../../AmuletCore/ -lAmuletCore

INCLUDEPATH += $$PWD/../../AmuletCore
DEPENDPATH += $$PWD/../../AmuletCore

OTHER_FILES += \
    codec_lame.json
