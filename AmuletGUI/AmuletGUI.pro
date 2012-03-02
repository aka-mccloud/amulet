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
    drop_table_view.cpp \
    properties_dialog.cpp \
    about_dialog.cpp

HEADERS  += main_window.hpp \
    queue_model.hpp \
    drop_table_view.hpp \
    properties_dialog.h \
    about_dialog.h

FORMS    += main_window.ui \
    properties_dialog.ui \
    about_dialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AmuletCore/release/ -lAmuletCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AmuletCore/debug/ -lAmuletCore
else:symbian: LIBS += -lAmuletCore
else:unix: LIBS += -L$$OUT_PWD/../AmuletCore/ -lAmuletCore

INCLUDEPATH += $$PWD/../AmuletCore
DEPENDPATH += $$PWD/../AmuletCore

RESOURCES += \
    amulet.qrc
