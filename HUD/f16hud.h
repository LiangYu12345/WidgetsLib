#ifndef F16HUD_H
#define F16HUD_H

#include "../widgetslib_global.h"

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QSet>
#include <QPair>
#include "AirSpeedScalesItem.h"
#include "BankAngleIndicator.h"
#include "BaroAltitudeScales.h"
#include "RollIndicator.h"
#include "FlightPathMarker.h"
#include "GreatCircleSteeringCue.h"
#include "SteerpointSymbol.h"
#include "GunCross.h"
#include "OffsetAimpoint.h"
#include "SoiSymbol.h"
#include "HeadingScale.h"
#include "HorizonLine.h"
#include "CurrentG.h"
#include "MaxGs.h"
#include "OperatingMode.h"
#include "MachNumber.h"
#include "MasterArm.h"
#include "RadarAltitude.h"
#include "AltitudeLowSetting.h"
#include "SlantRange.h"
#include "TimeToSteerpoint.h"
#include "DistanceToSteerpoint.h"
#include "LabelBeacon.h"
#include "labelbeaconline.h"
#include "PitchAttitudeBars.h"

#include "MissileReticle.h"
#include "TargetAspect.h"
#include "Aim-9MissileDiamond.h"
#include "T-DBox.h"
#include "TargetRange.h"
#include "AAMissileType.h"
#include "MleRange.h"
#include "MissileLaunchEnvelope.h"
#include "TargetClosureRate.h"
#include "Pre-launchAim-9TimeOfFlight.h"
#include "TargetSlantRange.h"
/*!
 * \brief The HUD class
 * \note
 */
class WIDGETSLIB_EXPORT F16HUD : public QGraphicsView
{
    Q_OBJECT
public:
    F16HUD(QWidget *parent = nullptr);
    ~F16HUD();
    /// 设置屏幕分辨率，便于某些在屏幕浮动元素的坐标定位
    void setScreenResolution(int w, int h);
    /// 获取屏幕分辨率
    const QSize getScreenResolution();
    /// 设置某元素在屏幕中的位置
    void setScreenPos(QGraphicsItem *item, int x, int y);
    /// 获取某元素在屏幕中的位置
    QPoint screenPos(const QGraphicsItem *item) const;
    /// 激活元素，该功能用在Decluttering Filtter
    void activeItem(QGraphicsItem &item);
    /// 禁用元素，该功能用在Decluttering Filtter
    void inactiveItem(QGraphicsItem &item);
    /// 切换模式, /note ： 1.NAV导航模式  2。空空模式
    void switcherMode(int mode);
public: // 为了方便外部调用，综合考虑之后将所有元素公开为public
    // 左
    AirSpeedScalesItem m_airspeedscales;
    SoiSymbol m_soisymbol;
    CurrentG m_currentg;

    // 左下
    MaxGs m_maxgs;
    OperatingMode m_operatingmode;

    MasterArm m_masterarm;
    MachNumber m_machnumber;
    // 中上
    BankAngleIndicator m_bankangleindicator;
    FlightPathMarker m_flightpathmarker;
    GreatCircleSteeringCue m_greatcirclesteeringcue;
    SteerpointSymbol m_steerpointsymbol;
    GunCross m_guncross;

    PitchAttitudeBars m_pitchattitudebars;
    //中线
    HorizonLine m_horizonline;
    LabelBeacon m_leftlabelbeacon;
    LabelBeaconLine m_leftlabelbeaconline;
    LabelBeacon m_rightlabelbeacon;
    LabelBeaconLine m_rightlabelbeaconline;
    //中下
    OffsetAimpoint m_offsetaimpoint;
    HeadingScale m_headingscale;
    f16RollIndicator m_rollindicator;
    // 右
    BaroAltitudeScales m_baroaltitudescales;
    // 右下
    RadarAltitude m_radaraltitude;
    AltitudeLowSetting m_altitudelowsetting;
    SlantRange m_slantrange;
    TimeToSteerpoint m_timetosteerpoint;
    DistanceToSteerpoint m_distancetosteerpoint;


    //中
    MissileReticle m_missilereticle;
    //TargetAspect m_targetaspect;
    Aim9MissileDiamond m_aim9missilediamond;
    TDBox m_tdbox;
    TargetRange m_targetrange;
    AAMissileType m_aamissiletype;
    MleRange m_mlerange;
    MissileLaunchEnvelope m_missilelaunchenvelope;
    TargetClosureRate m_targetclosurerate;
    PrelaunchAim9TimeOfFlight m_prelaunchaim9timeofflight;
    TargetSlantRange m_targetslantrange;
private:
    void initScene();

private:
    QSize m_res = {1920, 1080};  /// 分辨率

    // Decluttering helper
    QSet<QGraphicsItem*>    m_activeItems;
    int m_mode;
};


#endif // F16HUD_H
