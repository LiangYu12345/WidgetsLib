QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += WIDGETSLIB_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    Button/switchbutton.cpp \
    Button/dragbutton.cpp \
    HUD/AAMissileType.cpp \
    HUD/Aim-9MissileDiamond.cpp \
    HUD/AirSpeedScalesItem.cpp \
    HUD/AltitudeLowSetting.cpp \
    HUD/BankAngleIndicator.cpp \
    HUD/BaroAltitudeScales.cpp \
    HUD/CurrentG.cpp \
    HUD/DistanceToSteerpoint.cpp \
    HUD/f16hud.cpp \
    HUD/FlightPathMarker.cpp \
    HUD/GreatCircleSteeringCue.cpp \
    HUD/GunCross.cpp \
    HUD/HeadingScale.cpp \
    HUD/HorizonLine.cpp \
    HUD/huditem.cpp \
    HUD/LabelBeacon.cpp \
    HUD/MachNumber.cpp \
    HUD/MasterArm.cpp \
    HUD/MaxGs.cpp \
    HUD/MissileLaunchEnvelope.cpp \
    HUD/MissileReticle.cpp \
    HUD/MleRange.cpp \
    HUD/OffsetAimpoint.cpp \
    HUD/OperatingMode.cpp \
    HUD/PitchAttitudeBars.cpp \
    HUD/Pre-launchAim-9TimeOfFlight.cpp \
    HUD/RadarAltitude.cpp \
    HUD/RollIndicator.cpp \
    HUD/SlantRange.cpp \
    HUD/SoiSymbol.cpp \
    HUD/Steerpoint.cpp \
    HUD/SteerpointSymbol.cpp \
    HUD/TargetAspect.cpp \
    HUD/TargetClosureRate.cpp \
    HUD/TargetRange.cpp \
    HUD/TargetSlantRange.cpp \
    HUD/T-DBox.cpp \
    HUD/TimeToSteerpoint.cpp \
    HUD/wingloong2hud.cpp \
    MissileConfigure/emptymissile.cpp \
    MissileConfigure/f35frontview.cpp \
    MissileConfigure/f35missileconfigure.cpp \
    MissileConfigure/f35weaponconfigure.cpp \
    MissileConfigure/infraredmissile.cpp \
    MissileConfigure/j20frontview.cpp \
    MissileConfigure/j20missileconfigure.cpp \
    MissileConfigure/j20weaponconfigure.cpp \
    MissileConfigure/missile.cpp \
    MissileConfigure/missileconfigure.cpp \
    MissileConfigure/radarmissile.cpp \
    MissileConfigure/weaponconfigure.cpp \
    MissileConfigure/xxweapon.cpp \
    MultileListView/areainformationdisplay.cpp \
    MultileListView/multilelistview.cpp \
    MultileListView/multilelistviewitem.cpp \
    PFD/rollpitch.cpp \
    SidePanel/drawerpanel.cpp \
    Table/execltablewidget.cpp \
    Table/polygontablewidget.cpp \
    Table/tablewidget.cpp \
    Table/waypointtablewidget.cpp

HEADERS += \
    widgetslib_global.h \
    Button/dragbutton.h \
    Button/switchbutton.h \
    HUD/AAMissileType.h \
    HUD/Aim-9MissileDiamond.h \
    HUD/AirSpeedScalesItem.h \
    HUD/AltitudeLowSetting.h \
    HUD/BankAngleIndicator.h \
    HUD/BaroAltitudeScales.h \
    HUD/CurrentG.h \
    HUD/DistanceToSteerpoint.h \
    HUD/f16hud.h \
    HUD/FlightPathMarker.h \
    HUD/GreatCircleSteeringCue.h \
    HUD/GunCross.h \
    HUD/HeadingScale.h \
    HUD/HorizonLine.h \
    HUD/huditem.h \
    HUD/LabelBeacon.h \
    HUD/MachNumber.h \
    HUD/MasterArm.h \
    HUD/MaxGs.h \
    HUD/MissileLaunchEnvelope.h \
    HUD/MissileReticle.h \
    HUD/MleRange.h \
    HUD/OffsetAimpoint.h \
    HUD/OperatingMode.h \
    HUD/PitchAttitudeBars.h \
    HUD/Pre-launchAim-9TimeOfFlight.h \
    HUD/RadarAltitude.h \
    HUD/RollIndicator.h \
    HUD/SlantRange.h \
    HUD/SoiSymbol.h \
    HUD/Steerpoint.h \
    HUD/SteerpointSymbol.h \
    HUD/TargetAspect.h \
    HUD/TargetClosureRate.h \
    HUD/TargetRange.h \
    HUD/TargetSlantRange.h \
    HUD/T-DBox.h \
    HUD/TimeToSteerpoint.h \
    HUD/wingloong2hud.h \
    MissileConfigure/emptymissile.h \
    MissileConfigure/f35frontview.h \
    MissileConfigure/f35missileconfigure.h \
    MissileConfigure/f35weaponconfigure.h \
    MissileConfigure/infraredmissile.h \
    MissileConfigure/j20frontview.h \
    MissileConfigure/j20missileconfigure.h \
    MissileConfigure/j20weaponconfigure.h \
    MissileConfigure/missile.h \
    MissileConfigure/missileconfigure.h \
    MissileConfigure/radarmissile.h \
    MissileConfigure/weaponconfigure.h \
    MissileConfigure/xxweapon.h \
    MultileListView/areainformationdisplay.h \
    MultileListView/multilelistview.h \
    MultileListView/multilelistviewitem.h \
    PFD/rollpitch.h \
    SidePanel/drawerpanel.h \
    Table/execltablewidget.h \
    Table/polygontablewidget.h \
    Table/tablewidget.h \
    Table/waypointtablewidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
