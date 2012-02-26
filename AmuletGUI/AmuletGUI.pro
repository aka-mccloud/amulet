#-------------------------------------------------
#
# Project created by QtCreator 2012-02-26T12:17:48
#
#-------------------------------------------------

QT       += core gui

TARGET = AmuletGUI
TEMPLATE = app


SOURCES += main.cpp\
        main_window.cpp \
    queue_model.cpp \
    drop_table_view.cpp

HEADERS  += main_window.hpp \
    queue_model.hpp \
    drop_table_view.hpp

FORMS    += main_window.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AmuletCore/release/ -lAmuletCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AmuletCore/debug/ -lAmuletCore
else:symbian: LIBS += -lAmuletCore
else:unix: LIBS += -L$$OUT_PWD/../AmuletCore/ -lAmuletCore

INCLUDEPATH += $$PWD/../AmuletCore
DEPENDPATH += $$PWD/../AmuletCore
