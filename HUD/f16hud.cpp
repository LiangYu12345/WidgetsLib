#include "f16hud.h"
#include <QOpenGLWidget>
#include <QTimer>

static void TextItemStyle(QGraphicsSimpleTextItem &item, int fontSize = 15)
{
    item.setFont({"Microsoft Yahei", fontSize});
    item.setPen({Qt::white});
    item.setBrush({Qt::white});
}

F16HUD::F16HUD(QWidget *parent) : QGraphicsView(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setRenderHint(QPainter::Antialiasing, true);
    this->setStyleSheet("background:transparent; border:0px");

    //
    initScene();
}

F16HUD::~F16HUD()
{

}

void F16HUD::setScreenResolution(int w, int h)
{
    m_res.setWidth(w);
    m_res.setHeight(h);
}

const QSize F16HUD::getScreenResolution()
{
    return m_res;
}

void F16HUD::setScreenPos(QGraphicsItem *item, int x, int y)
{
    auto centerX = m_res.width() / 2;
    auto centerY = m_res.height() / 2;
    item->setPos(x - centerX, y - centerY);
}

QPoint F16HUD::screenPos(const QGraphicsItem *item) const
{
    auto centerX = m_res.width() / 2;
    auto centerY = m_res.height() / 2;
    return {centerX + int(item->x()), centerY + int(item->y())};
}

void F16HUD::activeItem(QGraphicsItem &item)
{
    if(m_activeItems.contains(&item))
        return;
    m_activeItems.insert(&item);
    this->scene()->addItem(&item);
}

void F16HUD::inactiveItem(QGraphicsItem &item)
{
    if(!m_activeItems.contains(&item))
        return;
    // maybe faild when the item isn't called by @activeItem, we can ignore it
    m_activeItems.remove(&item);
    this->scene()->removeItem(&item);
}

void F16HUD::setDeclutterLevel(int level)
{
//    bool active = level == 0;
//    // active or inactive all at first
//    active ? activeItem(polarityLabel)     :    inactiveItem(polarityLabel);
//    active ? activeItem(sensorLabel)       :    inactiveItem(sensorLabel);
//    active ? activeItem(fovIndicator)      :    inactiveItem(fovIndicator);
//    active ? activeItem(zoomIndicator)     :    inactiveItem(zoomIndicator);
//    active ? activeItem(digitFovLabel)     :    inactiveItem(digitFovLabel);

//    active ? activeItem(elIndicator)       :    inactiveItem(elIndicator);
//    active ? activeItem(elLabel)           :    inactiveItem(elLabel);
//    active ? activeItem(azIndicator)       :    inactiveItem(azIndicator);
//    active ? activeItem(azLabel)           :    inactiveItem(azLabel);
//    active ? activeItem(sateLabel)         :    inactiveItem(sateLabel);
//    active ? activeItem(sateIcon)          :    inactiveItem(sateIcon);

//    active ? activeItem(FGLIndicator)      :    inactiveItem(FGLIndicator);
//    active ? activeItem(FGLValueLabel)     :    inactiveItem(FGLValueLabel);
//    active ? activeItem(FGLLabel)          :    inactiveItem(FGLLabel);

//    active ? activeItem(crosshair)         :    inactiveItem(crosshair);
//    active ? activeItem(northIndicator)    :    inactiveItem(northIndicator);
//    active ? activeItem(messageLabel)      :    inactiveItem(messageLabel);

//    active ? activeItem(acftLabel)         :    inactiveItem(acftLabel);
//    active ? activeItem(acftLatLabel)      :    inactiveItem(acftLatLabel);
//    active ? activeItem(acftLonLabel)      :    inactiveItem(acftLonLabel);
//    active ? activeItem(acftAltLabel)      :    inactiveItem(acftAltLabel);
//    active ? activeItem(acftYawLabel)      :    inactiveItem(acftYawLabel);
//    active ? activeItem(acftGSLabel)       :    inactiveItem(acftGSLabel);

//    active ? activeItem(OSS1Label)         :    inactiveItem(OSS1Label);
//    active ? activeItem(OSS2Label)         :    inactiveItem(OSS2Label);
//    active ? activeItem(OSS3Label)         :    inactiveItem(OSS3Label);
//    active ? activeItem(OSS4Label)         :    inactiveItem(OSS4Label);
//    active ? activeItem(OSS5Label)         :    inactiveItem(OSS5Label);
//    active ? activeItem(OSS6Label)         :    inactiveItem(OSS6Label);

//    active ? activeItem(tgtLabel)          :    inactiveItem(tgtLabel);
//    active ? activeItem(tgtLatLabel)       :    inactiveItem(tgtLatLabel);
//    active ? activeItem(tgtLonLabel)       :    inactiveItem(tgtLonLabel);
//    active ? activeItem(tgtAltLabel)       :    inactiveItem(tgtAltLabel);
//    active ? activeItem(tgtRangeLabel)     :    inactiveItem(tgtRangeLabel);
//    active ? activeItem(tgtKphLabel)       :    inactiveItem(tgtKphLabel);

//    active ? activeItem(dateLabel)         :    inactiveItem(dateLabel);
//    active ? activeItem(timeLabel)         :    inactiveItem(timeLabel);
//    active ? activeItem(modeLabel)         :    inactiveItem(modeLabel);
//    active ? activeItem(laserLabel)        :    inactiveItem(laserLabel);

//    //active ? activeItem(trackingLable)     :    inactiveItem(trackingLable);
//    active ? activeItem(preTrackIndicator) :    inactiveItem(preTrackIndicator);
//    active ? activeItem(switchIndicator)   :    inactiveItem(switchIndicator);

//    if(level == 0)  // all have been actived
//        return;
//    //
//    if(level == 1) {
//        activeItem(sensorLabel);

//        activeItem(elIndicator);
//        activeItem(elLabel);
//        activeItem(azIndicator);
//        activeItem(azLabel);

//        activeItem(crosshair);
//        activeItem(northIndicator);

//        activeItem(acftLabel);
//        activeItem(acftLatLabel);
//        activeItem(acftLonLabel);
//        activeItem(acftAltLabel);
//        activeItem(acftYawLabel);
//        activeItem(acftGSLabel);

//        activeItem(tgtLabel);
//        activeItem(tgtLatLabel);
//        activeItem(tgtLonLabel);
//        activeItem(tgtAltLabel);
//        activeItem(tgtRangeLabel);
//        activeItem(tgtKphLabel);

//        activeItem(dateLabel);
//        activeItem(timeLabel);
//        activeItem(modeLabel);
//    }
//    else if(level == 2) {
//        activeItem(sensorLabel);

//        activeItem(crosshair);
//        activeItem(northIndicator);

//        activeItem(OSS1Label);
//        activeItem(OSS2Label);
//        activeItem(OSS3Label);
//        activeItem(OSS4Label);
//        activeItem(OSS5Label);
//        activeItem(OSS6Label);

//        activeItem(dateLabel);
//        activeItem(timeLabel);
//    }
//    else if(level == 3) {
//        activeItem(crosshair);
//        activeItem(northIndicator);
//    }
}

void F16HUD::triggerFGLHUD(const QString &label)
{
//    static QTimer *timer = nullptr;
//    if(timer)
//        timer->start(5e3);
//    else {
//        timer = new QTimer(this);
//        connect(timer, &QTimer::timeout, this, [&](){
//            FGLLabel.hide();
//            FGLValueLabel.hide();
//            FGLIndicator.hide();
//        });
//    }

//    FGLLabel.setText(label);
//    FGLLabel.show();
//    FGLValueLabel.show();
//    FGLIndicator.show();
}

void F16HUD::setLaserEnable(const QString &text)
{
//    laserLabel.setText(text);
//    laserLabel.show();
}

void F16HUD::setLaserDisable()
{
//    laserLabel.hide();
}

void F16HUD::setLaserWork(int timeoutSecond)
{
//    laserIndicator.trigger(timeoutSecond);
//    laserLabel.setBorder({Qt::white});
//    if(timeoutSecond != 0) {
//        QTimer::singleShot(timeoutSecond * 1e3, this, [&](){
//            laserLabel.setBorder(Qt::NoPen);
//        });
//    }
}

void F16HUD::setLaserStop()
{
//    laserIndicator.stop();
//    laserLabel.setBorder(Qt::NoPen);
}

void F16HUD::initScene()
{
    auto scene = new QGraphicsScene;
    this->setScene(scene);
    // 综合考虑之后，将屏幕中心设置为坐标原点
    scene->setSceneRect(-1920/2, -1080/2, 1920, 1080);

    // 左
    activeItem(m_airspeedscales);
    m_airspeedscales.setValue(480);
    m_airspeedscales.setPos(-480,-20);

    activeItem(m_soisymbol);
    m_soisymbol.setPos(-460,-240);

    activeItem(m_currentg);
    m_currentg.setPos(-440,-200);
    m_currentg.setValue(1.0);
    // 左下
    activeItem(m_maxgs);
    m_maxgs.setPos(-440,300);
    m_maxgs.setValue(2.6);

    activeItem(m_operatingmode);
    m_operatingmode.setPos(-440,330);
    m_operatingmode.setValue(u8"NAV");

    activeItem(m_machnumber);
    m_machnumber.setPos(-365,280);
    m_machnumber.setValue(0.88);

    activeItem(m_masterarm);
    m_masterarm.setPos(-400,240);
    m_masterarm.setValue(u8"SIM");

    // 中上
    activeItem(m_guncross);
    m_guncross.setPos(0,-400);

    activeItem(m_bankangleindicator);
    m_bankangleindicator.setPos(0,-150);

    activeItem(m_flightpathmarker);
    m_flightpathmarker.setPos(0,-190);

    activeItem(m_greatcirclesteeringcue);
    m_greatcirclesteeringcue.setPos(100,-170);

    activeItem(m_steerpointsymbol);
    m_steerpointsymbol.setPos(200,-100);

    activeItem(m_pitchattitudebars);
    m_pitchattitudebars.setPos(0,-50);


    //中
    activeItem(m_horizonline);
    m_horizonline.setPos(0,-40);

    activeItem(m_leftlabelbeacon);
    m_leftlabelbeacon.setPos(-600,-80);
    m_leftlabelbeacon.setDirection(4);
    m_leftlabelbeacon.setValue(u8"480");

    activeItem(m_rightlabelbeacon);
    m_rightlabelbeacon.setPos(480,-80);
    m_rightlabelbeacon.setDirection(3);
    m_rightlabelbeacon.setValue(u8"12,500");

    //中下
    activeItem(m_rollindicator);
    m_rollindicator.setPos(0,0);

    activeItem(m_offsetaimpoint);
    m_offsetaimpoint.setPos(-150,50);

    activeItem(m_headingscale);
    m_headingscale.setPos(0,150);

    // 右
    activeItem(m_baroaltitudescales);
    m_baroaltitudescales.setPos(480,-20);
    m_baroaltitudescales.setValue(12500);

    //右下
    activeItem(m_radaraltitude);
    m_radaraltitude.setPos(480,280);
    m_radaraltitude.setValue(11850);

    activeItem(m_altitudelowsetting);
    m_altitudelowsetting.setPos(480,310);
    m_altitudelowsetting.setValue(200);

    activeItem(m_slantrange);
    m_slantrange.setPos(480,340);
    m_slantrange.setValue(u8"B018.7");

    activeItem(m_timetosteerpoint);
    m_timetosteerpoint.setPos(480,370);
    m_timetosteerpoint.setValue(u8"01 53");

    activeItem(m_distancetosteerpoint);
    m_distancetosteerpoint.setPos(480,400);
    m_distancetosteerpoint.setValue(u8"018");
    m_distancetosteerpoint.setDisToValue(u8"03");





    //中
//    activeItem(m_guncross);
//    m_guncross.setPos(0,-400);

//    activeItem(m_missilereticle);
//    m_missilereticle.setPos(0,-150);


//    activeItem(m_leftlabelbeacon);
//    m_leftlabelbeacon.setPos(-600,-80);
//    m_leftlabelbeacon.setDirection(4);
//    m_leftlabelbeacon.setValue(u8"480");

//    activeItem(m_rightlabelbeacon);
//    m_rightlabelbeacon.setPos(480,-80);
//    m_rightlabelbeacon.setDirection(3);
//    m_rightlabelbeacon.setValue(u8"12,500");

//    activeItem(m_targetrange);
//    m_targetrange.setPos(0,0);

//    activeItem(m_flightpathmarker);
//    m_flightpathmarker.setPos(0,100);
//    //左

//    activeItem(m_aim9missilediamond);
//    m_aim9missilediamond.setPos(-350,-150);


//    activeItem(m_tdbox);
//    m_tdbox.setPos(0,0);

//    //左下

//    activeItem(m_aamissiletype);
//    m_aamissiletype.setPos(-450,150);

//    //右

//    activeItem(m_mlerange);
//    m_mlerange.setPos(450,-350);


//    activeItem(m_missilelaunchenvelope);
//    m_missilelaunchenvelope.setPos(460,-50);

//    activeItem(m_targetclosurerate);
//    m_targetclosurerate.setPos(380,0);
//    //右下

//    activeItem(m_prelaunchaim9timeofflight);
//    m_prelaunchaim9timeofflight.setPos(450,150);

//    activeItem(m_targetslantrange);
//    m_targetslantrange.setPos(400,250);
}
