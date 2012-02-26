#-------------------------------------------------
#
# Project created by QtCreator 2012-02-25T20:12:15
#
#-------------------------------------------------

QT       -= gui

TARGET = AmuletCore
TEMPLATE = lib

DEFINES += AMULETCORE_LIBRARY

SOURCES += \
    worker_pool.cpp \
    converter_worker.cpp \
    converter_service.cpp \
    converter_factory.cpp \
    codec_properties.cpp \
    codec_factory.cpp \
    plugins_provider.cpp \
    queue_item.cpp \
    queue.cpp

HEADERS +=\
        AmuletCore_global.hpp \
    worker_pool.hpp \
    iworker.hpp \
    iencoder_process.hpp \
    idecoder_process.hpp \
    icodec_provider.hpp \
    icodec_plugin.hpp \
    converter_worker.hpp \
    converter_service.hpp \
    converter_factory.hpp \
    codec_properties.hpp \
    codec_factory.hpp \
    plugins_provider.hpp \
    queue_item.hpp \
    queue.hpp

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE734D53A
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = AmuletCore.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
