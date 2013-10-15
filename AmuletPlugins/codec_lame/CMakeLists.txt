project(CodecLame)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${AmuletCore_SOURCE_DIR}
)

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

qt4_wrap_ui(CodecLame_SOURCES_UI ${CodecLame_UI})
qt4_wrap_cpp(CodecLame_SOURCES_MOC ${CodecLame_HEADERS})

add_library(codec_lame SHARED
    ${CodecLame_SOURCES}
    ${CodecLame_SOURCES_UI}
    ${CodecLame_SOURCES_MOC}
)

target_link_libraries(codec_lame
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    amulet_core
)

add_custom_command(TARGET codec_lame POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:codec_lame> ${CMAKE_CURRENT_BINARY_DIR}/../$<TARGET_FILE_NAME:codec_lame> VERBATIM)
install(TARGETS codec_lame DESTINATION share/amulet/plugins)
