project(AmuletGUI)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${AmuletCore_SOURCE_DIR}
)

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

set (AmuletGUI_QRC
    amulet.qrc
)

qt4_wrap_ui(AmuletGUI_SOURCES_UI ${AmuletGUI_UI})
qt4_wrap_cpp(AmuletGUI_SOURCES_MOC ${AmuletGUI_HEADERS})
qt4_add_resources(AmuletGUI_SOURCES_QRC ${AmuletGUI_QRC})

add_executable(amulet
    ${AmuletGUI_SOURCES}
    ${AmuletGUI_SOURCES_UI}
    ${AmuletGUI_SOURCES_MOC}
    ${AmuletGUI_SOURCES_QRC}
)

target_link_libraries(amulet
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    amulet_core
)

install(TARGETS amulet DESTINATION bin)