cmake_minimum_required(VERSION 3.5)

project(WidgetsLib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(WidgetsLib SHARED
  widgetslib_global.h
  HUD/huditem.h
  HUD/huditem.cpp
  HUD/wingloong2hud.h
  HUD/wingloong2hud.cpp
)
add_library(Lib::Widgets ALIAS ${PROJECT_NAME})

#
target_link_libraries(WidgetsLib PRIVATE Qt5::Widgets)

#
target_compile_definitions(WidgetsLib PRIVATE WIDGETSLIB_LIBRARY)

#
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION install)
