#-------------------------------------------------
#
# Project created by QtCreator 2012-02-25T19:55:08
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = AmuletConsole
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AmuletCore/release/ -lAmuletCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AmuletCore/debug/ -lAmuletCore
else:symbian: LIBS += -lAmuletCore
else:unix: LIBS += -L$$OUT_PWD/../AmuletCore/ -lAmuletCore

INCLUDEPATH += $$PWD/../AmuletCore
DEPENDPATH += $$PWD/../AmuletCore
