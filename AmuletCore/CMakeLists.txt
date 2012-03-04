project(AmuletCore)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
)

set(AmuletCore_SOURCES
    codec_factory.cpp
    codec_properties.cpp
    converter_factory.cpp
    converter_service.cpp
    converter_worker.cpp
    plugin_loader.cpp
    plugins_provider.cpp
    queue.cpp
    queue_item.cpp
    worker_pool.cpp
)

set(AmuletCore_HEADERS
    converter_factory.hpp
    converter_service.hpp
    converter_worker.hpp
    icodec_widget.hpp
    queue.hpp
    queue_item.hpp
    worker_pool.hpp
)

qt4_wrap_cpp(AmuletCore_SOURCES_MOC ${AmuletCore_HEADERS})

add_library(AmuletCore SHARED
    ${AmuletCore_SOURCES}
    ${AmuletCore_SOURCES_MOC}
)

target_link_libraries(AmuletCore
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
)
