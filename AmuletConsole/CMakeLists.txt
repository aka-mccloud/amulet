cmake_minimum_required(VERSION 3.16)

project(AmuletConsole)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(AmuletConsole_SOURCES
    main.cpp
)

add_executable(amulet_console
    ${AmuletConsole_SOURCES}
)

target_link_libraries(amulet_console
    Qt5::Core
    amulet_core
)
