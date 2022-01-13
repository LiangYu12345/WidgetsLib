cmake_minimum_required(VERSION 3.5)

project(WidgetsLib LANGUAGES CXX)
set(CMAKE_DEBUG_POSTFIX d)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} SHARED
  widgetslib_global.h
  Button/dragbutton.h
  Button/dragbutton.cpp
  HUD/huditem.h
  HUD/huditem.cpp
  HUD/f16hud.h
  HUD/f16hud.cpp
  HUD/AirSpeedScalesItem.h
  HUD/AirSpeedScalesItem.cpp
  HUD/AltitudeLowSetting.h
  HUD/AltitudeLowSetting.cpp
  HUD/BankAngleIndicator.h
  HUD/BankAngleIndicator.cpp
  HUD/BaroAltitudeScales.h
  HUD/BaroAltitudeScales.cpp
  HUD/CurrentG.h
  HUD/CurrentG.cpp
  HUD/DistanceToSteerpoint.h
  HUD/DistanceToSteerpoint.cpp
  HUD/FlightPathMarker.h
  HUD/FlightPathMarker.cpp
  HUD/GreatCircleSteeringCue.h
  HUD/GreatCircleSteeringCue.cpp
  HUD/GunCross.h
  HUD/GunCross.cpp
  HUD/HeadingScale.h
  HUD/HeadingScale.cpp
  HUD/HorizonLine.h
  HUD/HorizonLine.cpp
  HUD/MachNumber.h
  HUD/MachNumber.cpp
  HUD/MasterArm.h
  HUD/MasterArm.cpp
  HUD/MaxGs.h
  HUD/MaxGs.cpp
  HUD/OffsetAimpoint.h
  HUD/OffsetAimpoint.cpp
  HUD/OperatingMode.h
  HUD/OperatingMode.cpp
  HUD/PitchAttitudeBars.h
  HUD/PitchAttitudeBars.cpp
  HUD/RadarAltitude.h
  HUD/RadarAltitude.cpp
  HUD/RollIndicator.h
  HUD/RollIndicator.cpp
  HUD/SlantRange.h
  HUD/SlantRange.cpp
  HUD/SoiSymbol.h
  HUD/SoiSymbol.cpp
  HUD/SteerpointSymbol.h
  HUD/SteerpointSymbol.cpp
  HUD/TimeToSteerpoint.h
  HUD/TimeToSteerpoint.cpp
)
add_library(Lib::Widgets ALIAS ${PROJECT_NAME})


find_package(Qt5 COMPONENTS Widgets REQUIRED)
#
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

#
target_compile_definitions(${PROJECT_NAME} PRIVATE WIDGETSLIB_LIBRARY)

#
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION install)
