#ifndef HUD_H
#define HUD_H

#include "widgetslib_global.h"

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QSet>
#include <QPair>
#include "huditem.h"

/*!
 * \brief The HUD class
 * \note 绿色元素在CSEO+项目不需要显示，在此保留代码在以后完善到其他项目
 */
class WingLoong2HUD : public QGraphicsView
{
    Q_OBJECT
public:
    WingLoong2HUD(QWidget *parent = nullptr);
    /// 设置屏幕分辨率，便于某些在屏幕浮动元素的坐标定位
    void setScreenResolution(int w, int h);
    /// 获取屏幕分辨率
    const QSize getScreenResolution();
    /// 设置某元素在屏幕中的位置
    void setScreenPos(QGraphicsItem *item, int x, int y);
    /// 获取某元素在屏幕中的位置
    QPoint screenPos(const QGraphicsItem *item) const;
    /// 显示提示信息 \param timeout 0代表常显
    void  showMessage(const QString &message, int timeout = 0);
    /// 清除提示信息
    void  clearMessage();
    /// 激活元素，该功能用在Decluttering Filtter
    void activeItem(QGraphicsItem &item);
    /// 禁用元素，该功能用在Decluttering Filtter
    void inactiveItem(QGraphicsItem &item);
    /*!
     * \brief 字符、指示器过滤等级
     * \param level
     * Level 0. none indcator decluttered;
     * Level 1. only crosshair, north indicator, sensor name, LOS Az and El indicator, time and date,
     * model opration, target location, OSS menu and platform location, velocity and heading indicator appear;
     * Level 2. only crosshair, north indicator, sensor name, time and date and OSS menu appear;
     * Level 3. only crosshair and north indicator appears;
     */
    void setDeclutterLevel(int level);
    /// 触发FGL显示并在无操作5秒后隐藏（需要在值修改前触发)
    /// \param "FOCUS" "GAIN" "LEVEL"
    void triggerFGLHUD(const QString &label);
    /// 设置激光使能，显示激光模式文字
    void setLaserEnable(const QString &text);
    void setLaserDisable();
    /// 设置激光工作，激光闪烁光斑+激光模式外边框
    void setLaserWork(int timeoutSecond);
    void setLaserStop();

public: // 为了方便外部调用，综合考虑之后将所有元素公开为public
    // 左上
    LabelIndicator           polarityLabel;     ///< 极性(SWIR/FLIR Only)
    QGraphicsSimpleTextItem  sensorLabel;       ///< active sensor
    FOVIndicator             fovIndicator;      ///< FOV指示框
    ProgressIndicator        zoomIndicator;     ///< 缩放指示条
    QGraphicsSimpleTextItem  digitFovLabel;     ///< 数字变倍
    // 上
    YawIndicator            yawIndicator;   ///< 偏航角指示
    LabelIndicator          yawLable;       ///< 航向角
    LabelIndicator          trackingLable;  ///< 航迹角
    ELIndicator             elIndicator;    ///< EL俯仰指示
    QGraphicsSimpleTextItem elLabel;        ///< EL俯仰指示
    AZIndicator             azIndicator;    ///< EO方位指示
    QGraphicsSimpleTextItem azLabel;        ///< EO方位指示
    QGraphicsSimpleTextItem sateLabel;      ///< 卫星旁文字
    QGraphicsPixmapItem     sateIcon;       ///< 卫星图标
    // 右上
    // 左
    SpeedIndicator          speedIndicator; ///< 速度指示
    LabelIndicator          GSLabel;        ///< Ground Speed
    LabelIndicator          IASLabel;       ///< Indicated Air Speed
    LabelIndicator          AOALabel;       ///< Angle Of Attack
    ProgressIndicator       FGLIndicator;   ///< Focus\Gain\Level条
    QGraphicsSimpleTextItem FGLValueLabel;  ///< Focus\Gain\Level条数值
    QGraphicsSimpleTextItem FGLLabel;       ///< Focus\Gain\Level条文字
    // 中
    Crosshair               crosshair;      ///< 十字准心
    LaserIndicator          laserIndicator; ///< 激光指示
    NorthIndicator          northIndicator; ///< 指北针
    QGraphicsSimpleTextItem messageLabel;   ///< 提示信息
    // 右
    AltitudeIndicator altIndicator;   ///< 高度指示
    LabelIndicator    climbLabel;     ///< 爬升率
    LabelIndicator    homeHightLabel; ///< 场高
    LabelIndicator    altLabel;       ///< 海拔高度
    // 左下
    QGraphicsSimpleTextItem acftLabel;    ///< ACFT 固定文字
    QGraphicsSimpleTextItem acftLatLabel; ///< ACFT 纬
    QGraphicsSimpleTextItem acftLonLabel; ///< ACFT 经
    QGraphicsSimpleTextItem acftAltLabel; ///< ACFT 高
    QGraphicsSimpleTextItem acftYawLabel; ///< ACFT 航向
    QGraphicsSimpleTextItem acftGSLabel;  ///< ACFT Ground Speed
    // 下
    RollIndicator     rollIndicator;  ///< 滚转指示
    LabelIndicator    rollLabel;      ///< 滚转
    LabelIndicator    OSS1Label;      ///< OSS soft key
    LabelIndicator    OSS2Label;      ///< OSS soft key
    LabelIndicator    OSS3Label;      ///< OSS soft key
    LabelIndicator    OSS4Label;      ///< OSS soft key
    LabelIndicator    OSS5Label;      ///< OSS soft key
    LabelIndicator    OSS6Label;      ///< OSS soft key
    // 右下
    QGraphicsSimpleTextItem tgtLabel;      ///< TGT 固定文字
    QGraphicsSimpleTextItem tgtLatLabel;   ///< TGT 纬
    QGraphicsSimpleTextItem tgtLonLabel;   ///< TGT 经
    QGraphicsSimpleTextItem tgtAltLabel;   ///< TGT 高
    QGraphicsSimpleTextItem tgtRangeLabel; ///< TGT Laser Range-finding / Geo Range Calculation
    QGraphicsSimpleTextItem tgtKphLabel;   ///< TGT 预留给某未知类型的kph数值
    // 右右下
    QGraphicsSimpleTextItem dateLabel;   ///< 日期
    QGraphicsSimpleTextItem timeLabel;   ///< 时间
    QGraphicsSimpleTextItem modeLabel;   ///< 模式
    LabelIndicator          laserLabel;  ///< 激光(使用LabelIndicator是为了方便边框效果)
    // 浮动
    TrackIndicator    trackIndicator;    ///< 跟踪指示框
    PreTrackIndicator preTrackIndicator; ///< 上一次跟踪指示框
    SwitchIndicator   switchIndicator;   ///< 跟踪调整调整框

private:
    void initScene();

private:
    QSize m_res = {1920, 1080};  /// 分辨率

    // Decluttering helper
    QSet<QGraphicsItem*>    m_activeItems;
};


#endif // HUD_H
