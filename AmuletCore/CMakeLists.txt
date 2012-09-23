project(AmuletCore)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)

find_package(Qt4 REQUIRED)
find_package(Taglib REQUIRED)

include_directories(
    ${QT_INCLUDES}
    ${TAGLIB_INCLUDES}
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
    tag_data.cpp
    tag_engine.cpp
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

add_library(amulet_core SHARED
    ${AmuletCore_SOURCES}
    ${AmuletCore_SOURCES_MOC}
)

target_link_libraries(amulet_core
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${TAGLIB_LIBRARIES}
)

install(TARGETS amulet_core DESTINATION lib)