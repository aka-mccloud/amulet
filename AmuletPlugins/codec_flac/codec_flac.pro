#-------------------------------------------------
#
# Project created by QtCreator 2013-10-09T09:37:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = codec_flac
TEMPLATE = lib

DEFINES += CODEC_FLAC_LIBRARY

SOURCES += codec_flac.cpp \
    widget_flac.cpp \
    encoder_flac.cpp \
    decoder_flac.cpp \
    codec_provider_flac.cpp

HEADERS += \
    widget_flac.hpp \
    encoder_flac.hpp \
    decoder_flac.hpp \
    codec_provider_flac.hpp \
    codec_flac.hpp

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    widget_flac.ui


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../AmuletCore/release/ -lAmuletCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../AmuletCore/debug/ -lAmuletCore
else:unix: LIBS += -L$$OUT_PWD/../../AmuletCore/ -lAmuletCore

INCLUDEPATH += $$PWD/../../AmuletCore
DEPENDPATH += $$PWD/../../AmuletCore

OTHER_FILES += \
    codec_flac.json
