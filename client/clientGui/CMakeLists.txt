cmake_minimum_required(VERSION 3.5)

project(clientGui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets WebSockets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets WebSockets REQUIRED)

if(ANDROID)
  add_library(clientGui SHARED
    main.cpp
    widget.cpp
    widget.h
    widget.ui
  )
else()
  add_executable(clientGui
    main.cpp
    widget.cpp
    widget.h
    widget.ui
  )
endif()

target_link_libraries(clientGui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WebSockets)
