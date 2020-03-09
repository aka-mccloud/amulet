cmake_minimum_required(VERSION 3.16)

project(AmuletGUI)

include(GNUInstallDirs)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(AmuletGUI_SOURCES
    about_dialog.cpp
    drop_table_view.cpp
    main.cpp
    main_window.cpp
    properties_dialog.cpp
    queue_model.cpp
)

set(AmuletGUI_HEADERS
    about_dialog.hpp
    drop_table_view.hpp
    main_window.hpp
    properties_dialog.hpp
    queue_model.hpp
)

set (AmuletGUI_UI
    about_dialog.ui
    main_window.ui
    properties_dialog.ui
)

set (AmuletGUI_RC
    amulet.qrc
)

add_executable(amulet
    ${AmuletGUI_SOURCES}
    ${AmuletGUI_HEADERS}
    ${AmuletGUI_UI}
    ${AmuletGUI_RC}
)

target_include_directories(amulet PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(amulet
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    amulet_core
)

install(TARGETS amulet DESTINATION ${CMAKE_INSTALL_BINDIR})
