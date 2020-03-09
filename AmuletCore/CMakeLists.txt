cmake_minimum_required(VERSION 3.16)

project(AmuletCore)

include(GNUInstallDirs)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(TagLib REQUIRED IMPORTED_TARGET GLOBAL taglib)

set(AmuletCore_SOURCES
    codec_factory.cpp
    codec_properties.cpp
    converter_factory.cpp
    converter_service.cpp
    converter_worker.cpp
    plugin_loader.cpp
    plugins_provider.cpp
    queue_item.cpp
    queue.cpp
    tag_data.cpp
    tag_engine.cpp
    worker_pool.cpp
)

set(AmuletCore_HEADERS
    codec_factory.hpp
    codec_properties.hpp
    converter_factory.hpp
    converter_service.hpp
    converter_worker.hpp
    iworker.hpp
    plugin_loader.hpp
    plugins_provider.hpp
    queue_item.hpp
    queue.hpp
    tag_data.hpp
    tag_engine.hpp
    worker_pool.hpp
)

set(AmuletCore_PUBLIC_HEADERS
    AmuletCore_global.hpp
    icodec_plugin.hpp
    icodec_provider.hpp
    icodec_widget.hpp
    idecoder_process.hpp
    iencoder_process.hpp
)

add_library(amulet_core SHARED
    ${AmuletCore_SOURCES}
    ${AmuletCore_HEADERS}
    ${AmuletCore_PUBLIC_HEADERS}
)

target_include_directories(amulet_core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/amulet>
)

set_target_properties(amulet_core PROPERTIES
    PUBLIC_HEADER "${AmuletCore_PUBLIC_HEADERS}"
)

target_link_libraries(amulet_core
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    PkgConfig::TagLib
)

install(TARGETS amulet_core EXPORT AmuletCoreConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/amulet
)

install(EXPORT AmuletCoreConfig DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/amulet)

export (TARGETS amulet_core FILE AmuletCoreConfig.cmake)
