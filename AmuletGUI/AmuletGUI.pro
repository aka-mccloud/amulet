#-------------------------------------------------
#
# Project created by QtCreator 2013-10-09T09:39:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AmuletGUI
TEMPLATE = app


SOURCES += main.cpp \
    queue_model.cpp \
    properties_dialog.cpp \
    main_window.cpp \
    drop_table_view.cpp \
    about_dialog.cpp

HEADERS  += \
    queue_model.hpp \
    properties_dialog.hpp \
    main_window.hpp \
    drop_table_view.hpp \
    about_dialog.hpp

FORMS    += \
    properties_dialog.ui \
    main_window.ui \
    about_dialog.ui

RESOURCES += \
    amulet.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AmuletCore/release/ -lAmuletCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AmuletCore/debug/ -lAmuletCore
else:unix: LIBS += -L$$OUT_PWD/../AmuletCore/ -lAmuletCore

INCLUDEPATH += $$PWD/../AmuletCore
DEPENDPATH += $$PWD/../AmuletCore

win32 {
    INCLUDEPATH += "C:/Program Files/taglib/include"
    DEPENDPATH += "C:/Program Files/taglib/include"

    CONFIG(release, debug|release): LIBS += -L"C:/Program Files/taglib/lib/" -ltag
    else:CONFIG(debug, debug|release): LIBS += -L"C:/Program Files/taglib/lib/" -ltag
}

unix: LIBS += -ltag
