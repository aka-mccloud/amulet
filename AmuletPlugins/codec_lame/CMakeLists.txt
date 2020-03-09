cmake_minimum_required(VERSION 3.16)

project(CodecLame)

include(GNUInstallDirs)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(CodecLame_SOURCES
    codec_lame.cpp
    codec_provider_lame.cpp
    decoder_lame.cpp
    encoder_lame.cpp
    widget_lame.cpp
)

set(CodecLame_HEADERS
    codec_lame.hpp
    decoder_lame.hpp
    encoder_lame.hpp
    widget_lame.hpp
)

set(CodecLame_UI
    widget_lame.ui
)

add_library(codec_lame MODULE
    ${CodecLame_SOURCES}
    ${CodecLame_HEADERS}
    ${CodecLame_UI}
)

target_link_libraries(codec_lame
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    amulet_core
)

add_custom_command(TARGET codec_lame POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:codec_lame> ${CMAKE_CURRENT_BINARY_DIR}/../$<TARGET_FILE_NAME:codec_lame> VERBATIM)

install(TARGETS codec_lame DESTINATION ${CMAKE_INSTALL_LIBDIR}/amulet/plugins)
