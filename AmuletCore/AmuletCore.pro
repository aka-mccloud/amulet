#-------------------------------------------------
#
# Project created by QtCreator 2013-10-09T09:30:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AmuletCore
TEMPLATE = lib

DEFINES += AMULETCORE_LIBRARY

SOURCES += \
    worker_pool.cpp \
    tag_engine.cpp \
    tag_data.cpp \
    queue_item.cpp \
    queue.cpp \
    plugins_provider.cpp \
    plugin_loader.cpp \
    converter_worker.cpp \
    converter_service.cpp \
    converter_factory.cpp \
    codec_properties.cpp \
    codec_factory.cpp

HEADERS += \
    worker_pool.hpp \
    tag_engine.hpp \
    tag_data.hpp \
    queue_item.hpp \
    queue.hpp \
    plugins_provider.hpp \
    plugin_loader.hpp \
    iworker.hpp \
    iencoder_process.hpp \
    idecoder_process.hpp \
    icodec_widget.hpp \
    icodec_provider.hpp \
    icodec_plugin.hpp \
    converter_worker.hpp \
    converter_service.hpp \
    converter_factory.hpp \
    codec_properties.hpp \
    codec_factory.hpp \
    AmuletCore_global.hpp

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32 {
    INCLUDEPATH += "C:/Program Files/taglib/include"
    DEPENDPATH += "C:/Program Files/taglib/include"

    CONFIG(release, debug|release): LIBS += -L"C:/Program Files/taglib/lib/" -ltag
    else:CONFIG(debug, debug|release): LIBS += -L"C:/Program Files/taglib/lib/" -ltag
}

unix: LIBS += -ltag

