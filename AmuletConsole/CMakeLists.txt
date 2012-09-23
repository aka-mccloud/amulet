project(AmuletConsole)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${AmuletCore_SOURCE_DIR}
)

set(AmuletConsole_SOURCES
    main.cpp
)

add_executable(amulet_console
    ${AmuletConsole_SOURCES}
)

target_link_libraries(amulet_console
    ${QT_QTCORE_LIBRARY}
    amulet_core
)
