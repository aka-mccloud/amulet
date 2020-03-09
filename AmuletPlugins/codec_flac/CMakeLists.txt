cmake_minimum_required(VERSION 3.16)

project(CodecFlac)

include(GNUInstallDirs)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(CodecFlac_SOURCES
    codec_flac.cpp
    codec_provider_flac.cpp
    decoder_flac.cpp
    encoder_flac.cpp
    widget_flac.cpp
)

set(CodecFlac_HEADERS
    codec_flac.hpp
    decoder_flac.hpp
    encoder_flac.hpp
    widget_flac.hpp
)

set (CodecFlac_UI
    widget_flac.ui
)

add_library(codec_flac MODULE
    ${CodecFlac_SOURCES}
    ${CodecFlac_HEADERS}
    ${CodecFlac_UI}
)

target_link_libraries(codec_flac
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    amulet_core
)

add_custom_command(TARGET codec_flac POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:codec_flac> ${CMAKE_CURRENT_BINARY_DIR}/../$<TARGET_FILE_NAME:codec_flac> VERBATIM)

install(TARGETS codec_flac DESTINATION ${CMAKE_INSTALL_LIBDIR}/amulet/plugins)
