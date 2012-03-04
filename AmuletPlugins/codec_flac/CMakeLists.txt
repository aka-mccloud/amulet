project(CodecFlac)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${AmuletCore_SOURCE_DIR}
)

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

qt4_wrap_ui(CodecFlac_SOURCES_UI ${CodecFlac_UI})
qt4_wrap_cpp(CodecFlac_SOURCES_MOC ${CodecFlac_HEADERS})

add_library(codec_flac SHARED
    ${CodecFlac_SOURCES}
    ${CodecFlac_SOURCES_UI}
    ${CodecFlac_SOURCES_MOC}
)

target_link_libraries(codec_flac
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    AmuletCore
)

add_custom_command(TARGET codec_flac POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:codec_flac> ${CMAKE_CURRENT_BINARY_DIR}/../$<TARGET_FILE_NAME:codec_flac> VERBATIM)
install(TARGETS codec_flac DESTINATION share/amulet/plugins)