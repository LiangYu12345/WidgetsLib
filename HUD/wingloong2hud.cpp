#include "wingloong2hud.h"
#include <QOpenGLWidget>
#include <QTimer>

static void TextItemStyle(QGraphicsSimpleTextItem &item, int fontSize = 15)
{
    item.setFont({"Microsoft Yahei", fontSize});
    item.setPen({Qt::white});
    item.setBrush({Qt::white});
}

static void OSSStyle(LabelIndicator &label)
{
    label.setSize({70, 20});
    label.setBrush(Qt::NoBrush);
    label.setPen({Qt::white});
}

HUD::HUD(QWidget *parent) : QGraphicsView(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setRenderHint(QPainter::Antialiasing, true);
    this->setStyleSheet("background:transparent; border:0px");

    //
    initScene();
}

void HUD::setScreenResolution(int w, int h)
{
    m_res.setWidth(w);
    m_res.setHeight(h);
}

const QSize HUD::getScreenResolution()
{
    return m_res;
}

void HUD::setScreenPos(QGraphicsItem *item, int x, int y)
{
    auto centerX = m_res.width() / 2;
    auto centerY = m_res.height() / 2;
    item->setPos(x - centerX, y - centerY);
}

QPoint HUD::screenPos(const QGraphicsItem *item) const
{
    auto centerX = m_res.width() / 2;
    auto centerY = m_res.height() / 2;
    return {centerX + int(item->x()), centerY + int(item->y())};
}

void HUD::showMessage(const QString &message, int timeout)
{
    static QTimer *timer = nullptr;
    if(!timer) {
       timer = new QTimer(this);
       timer->setSingleShot(true);
       connect(timer, &QTimer::timeout, this, [=](){
           messageLabel.setVisible(false);
       });
    }
    //
    messageLabel.setText(message);
    messageLabel.setPos(-messageLabel.boundingRect().width()/2, messageLabel.y());
    messageLabel.setVisible(true);
    if(timeout)
        timer->start(timeout);
}

void HUD::clearMessage()
{
    messageLabel.setVisible(false);
}

void HUD::activeItem(QGraphicsItem &item)
{
    if(m_activeItems.contains(&item))
        return;
    m_activeItems.insert(&item);
    this->scene()->addItem(&item);
}

void HUD::inactiveItem(QGraphicsItem &item)
{
    if(!m_activeItems.contains(&item))
        return;
    // maybe faild when the item isn't called by @activeItem, we can ignore it
    m_activeItems.remove(&item);
    this->scene()->removeItem(&item);
}

void HUD::setDeclutterLevel(int level)
{
    bool active = level == 0;
    // active or inactive all at first
    active ? activeItem(polarityLabel)     :    inactiveItem(polarityLabel);
    active ? activeItem(sensorLabel)       :    inactiveItem(sensorLabel);
    active ? activeItem(fovIndicator)      :    inactiveItem(fovIndicator);
    active ? activeItem(zoomIndicator)     :    inactiveItem(zoomIndicator);
    active ? activeItem(digitFovLabel)     :    inactiveItem(digitFovLabel);

    active ? activeItem(elIndicator)       :    inactiveItem(elIndicator);
    active ? activeItem(elLabel)           :    inactiveItem(elLabel);
    active ? activeItem(azIndicator)       :    inactiveItem(azIndicator);
    active ? activeItem(azLabel)           :    inactiveItem(azLabel);
    active ? activeItem(sateLabel)         :    inactiveItem(sateLabel);
    active ? activeItem(sateIcon)          :    inactiveItem(sateIcon);

    active ? activeItem(FGLIndicator)      :    inactiveItem(FGLIndicator);
    active ? activeItem(FGLValueLabel)     :    inactiveItem(FGLValueLabel);
    active ? activeItem(FGLLabel)          :    inactiveItem(FGLLabel);

    active ? activeItem(crosshair)         :    inactiveItem(crosshair);
    active ? activeItem(northIndicator)    :    inactiveItem(northIndicator);
    active ? activeItem(messageLabel)      :    inactiveItem(messageLabel);

    active ? activeItem(acftLabel)         :    inactiveItem(acftLabel);
    active ? activeItem(acftLatLabel)      :    inactiveItem(acftLatLabel);
    active ? activeItem(acftLonLabel)      :    inactiveItem(acftLonLabel);
    active ? activeItem(acftAltLabel)      :    inactiveItem(acftAltLabel);
    active ? activeItem(acftYawLabel)      :    inactiveItem(acftYawLabel);
    active ? activeItem(acftGSLabel)       :    inactiveItem(acftGSLabel);

    active ? activeItem(OSS1Label)         :    inactiveItem(OSS1Label);
    active ? activeItem(OSS2Label)         :    inactiveItem(OSS2Label);
    active ? activeItem(OSS3Label)         :    inactiveItem(OSS3Label);
    active ? activeItem(OSS4Label)         :    inactiveItem(OSS4Label);
    active ? activeItem(OSS5Label)         :    inactiveItem(OSS5Label);
    active ? activeItem(OSS6Label)         :    inactiveItem(OSS6Label);

    active ? activeItem(tgtLabel)          :    inactiveItem(tgtLabel);
    active ? activeItem(tgtLatLabel)       :    inactiveItem(tgtLatLabel);
    active ? activeItem(tgtLonLabel)       :    inactiveItem(tgtLonLabel);
    active ? activeItem(tgtAltLabel)       :    inactiveItem(tgtAltLabel);
    active ? activeItem(tgtRangeLabel)     :    inactiveItem(tgtRangeLabel);
    active ? activeItem(tgtKphLabel)       :    inactiveItem(tgtKphLabel);

    active ? activeItem(dateLabel)         :    inactiveItem(dateLabel);
    active ? activeItem(timeLabel)         :    inactiveItem(timeLabel);
    active ? activeItem(modeLabel)         :    inactiveItem(modeLabel);
    active ? activeItem(laserLabel)        :    inactiveItem(laserLabel);

    //active ? activeItem(trackingLable)     :    inactiveItem(trackingLable);
    active ? activeItem(preTrackIndicator) :    inactiveItem(preTrackIndicator);
    active ? activeItem(switchIndicator)   :    inactiveItem(switchIndicator);

    if(level == 0)  // all have been actived
        return;
    //
    if(level == 1) {
        activeItem(sensorLabel);

        activeItem(elIndicator);
        activeItem(elLabel);
        activeItem(azIndicator);
        activeItem(azLabel);

        activeItem(crosshair);
        activeItem(northIndicator);

        activeItem(acftLabel);
        activeItem(acftLatLabel);
        activeItem(acftLonLabel);
        activeItem(acftAltLabel);
        activeItem(acftYawLabel);
        activeItem(acftGSLabel);

        activeItem(OSS1Label);
        activeItem(OSS2Label);
        activeItem(OSS3Label);
        activeItem(OSS4Label);
        activeItem(OSS5Label);
        activeItem(OSS6Label);

        activeItem(tgtLabel);
        activeItem(tgtLatLabel);
        activeItem(tgtLonLabel);
        activeItem(tgtAltLabel);
        activeItem(tgtRangeLabel);
        activeItem(tgtKphLabel);

        activeItem(dateLabel);
        activeItem(timeLabel);
        activeItem(modeLabel);
    }
    else if(level == 2) {
        activeItem(sensorLabel);

        activeItem(crosshair);
        activeItem(northIndicator);

        activeItem(OSS1Label);
        activeItem(OSS2Label);
        activeItem(OSS3Label);
        activeItem(OSS4Label);
        activeItem(OSS5Label);
        activeItem(OSS6Label);

        activeItem(dateLabel);
        activeItem(timeLabel);
    }
    else if(level == 3) {
        activeItem(crosshair);
        activeItem(northIndicator);
    }
}

void HUD::triggerFGLHUD(const QString &label)
{
    static QTimer *timer = nullptr;
    if(timer)
        timer->start(5e3);
    else {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [&](){
            FGLLabel.hide();
            FGLValueLabel.hide();
            FGLIndicator.hide();
        });
    }

    FGLLabel.setText(label);
    FGLLabel.show();
    FGLValueLabel.show();
    FGLIndicator.show();
}

void HUD::setLaserEnable(const QString &text)
{
    laserLabel.setText(text);
    laserLabel.show();
}

void HUD::setLaserDisable()
{
    laserLabel.hide();
}

void HUD::setLaserWork(int timeoutSecond)
{
    laserIndicator.trigger(timeoutSecond);
    laserLabel.setBorder({Qt::white});
    if(timeoutSecond != 0) {
        QTimer::singleShot(timeoutSecond * 1e3, this, [&](){
            laserLabel.setBorder(Qt::NoPen);
        });
    }
}

void HUD::setLaserStop()
{
    laserIndicator.stop();
    laserLabel.setBorder(Qt::NoPen);
}

void HUD::initScene()
{
    auto scene = new QGraphicsScene;
    this->setScene(scene);
    // 综合考虑之后，将屏幕中心设置为坐标原点
    scene->setSceneRect(-1920/2, -1080/2, 1920, 1080);

    // 左上
    activeItem(polarityLabel);
    activeItem(sensorLabel);
    activeItem(fovIndicator);
    activeItem(zoomIndicator);
    activeItem(digitFovLabel);
    polarityLabel.setSize({20, 20});
    polarityLabel.setPos(-650, -500);
    TextItemStyle(sensorLabel);
    sensorLabel.setText("TV");
    sensorLabel.setPos(polarityLabel.pos() + QPointF(20, -10));
    fovIndicator.setPos(polarityLabel.pos() + QPointF(35, 50));
    fovIndicator.setLevel(4);
    fovIndicator.setFov(30);
    zoomIndicator.setSize({100, 12});
    zoomIndicator.setPos(fovIndicator.pos() + QPointF(0, 50));
    TextItemStyle(digitFovLabel);
    digitFovLabel.setText("X2");
    digitFovLabel.setPos(fovIndicator.pos() + QPointF(fovIndicator.boundingRect().width()/2 + 5, -digitFovLabel.boundingRect().height()/2));

    // 上
//    activeItem(yawIndicator);
//    activeItem(yawLable);
//    activeItem(trackingLable);
    activeItem(elIndicator);
    activeItem(azIndicator);
    activeItem(elLabel);
    activeItem(azLabel);
    activeItem(sateLabel);
    activeItem(sateIcon);
    yawIndicator.setRange(15);
    yawIndicator.setPos(0, -450);
    yawLable.setText("180");
    yawLable.setArrowVisible(true);
    yawLable.setPos(yawIndicator.pos() - QPointF{0, 20});
    trackingLable.setText("000");
    trackingLable.setPos(yawLable.pos() - QPointF{0, yawLable.boundingRect().height()+5});
    elIndicator.setPos(yawIndicator.pos() + QPointF(310, 0));
    azIndicator.setValue(30);
    azIndicator.setPos(elIndicator.pos() + QPointF(80, 0));
    TextItemStyle(elLabel);
    elLabel.setText("2");
    elLabel.setPos(elIndicator.pos() + QPointF(20, 50));
    TextItemStyle(azLabel);
    azLabel.setText("30");
    azLabel.setPos(azIndicator.pos() + QPointF(10, 50));
    TextItemStyle(sateLabel);
    sateLabel.setText("HYBR");
    sateLabel.setPos(elLabel.pos() + QPointF(5, 30));
    sateIcon.setPixmap({":/satellite"});
    sateIcon.setPos(azLabel.pos() + QPointF(0, 25));

    // 左
//    activeItem(speedIndicator);
//    activeItem(GSLabel);
//    activeItem(IASLabel);
//    activeItem(AOALabel);
    activeItem(FGLIndicator);
    activeItem(FGLValueLabel);
    activeItem(FGLLabel);
    speedIndicator.setRange(200);
    speedIndicator.setPos(-600, 0);
    IASLabel.setText("0");
    IASLabel.setSize({40, 20});
    IASLabel.setPos(speedIndicator.pos() - QPointF{30, 0});
    GSLabel.setText("0");
    GSLabel.setSize({40, 20});
    GSLabel.setPos(IASLabel.pos() - QPointF(50, 0));
    AOALabel.setText("0.0");
    AOALabel.setSize({40, 20});
    AOALabel.setPos(speedIndicator.pos() + QPointF(40, -10));
    FGLIndicator.setSize({16, 220});
    FGLIndicator.setRange(0, 100);
    FGLIndicator.setValue(50);
    FGLIndicator.setPos(speedIndicator.pos() + QPointF(100, 100));
    auto gainRect = FGLIndicator.boundingRect();
    TextItemStyle(FGLValueLabel);
    FGLValueLabel.setText("50");
    FGLValueLabel.setPos(FGLIndicator.pos() + QPointF(0, -gainRect.height()/2 - FGLValueLabel.boundingRect().height() - 10));
    TextItemStyle(FGLLabel);
    FGLLabel.setText("FOCUS");
    FGLLabel.setPos(FGLIndicator.pos() + QPointF(-FGLLabel.boundingRect().width()/2, gainRect.height()/2 + 10));

    // 中
    activeItem(crosshair);
    activeItem(laserIndicator);
    activeItem(northIndicator);
    activeItem(messageLabel);
    crosshair.setText("34");
    TextItemStyle(messageLabel);
    messageLabel.setText("NO DTM avaliable - LLA estimated");
    messageLabel.setPos(-messageLabel.boundingRect().width()/2, 250);

    // 右
//    activeItem(altIndicator);
//    activeItem(climbLabel);
//    activeItem(homeHightLabel);
//    activeItem(altLabel);
    altIndicator.setValue(299);
    altIndicator.setPos(600, 0);
    homeHightLabel.setText("299");
    homeHightLabel.setSize({40, 20});
    homeHightLabel.setPos(altIndicator.pos() + QPointF{30, 0});
    altLabel.setText("299");
    altLabel.setSize({40, 20});
    altLabel.setPos(homeHightLabel.pos() + QPointF{50, 0});
    climbLabel.setText("8");
    climbLabel.setSize({40, 20});
    climbLabel.setPos(altIndicator.pos() - QPointF{40, 10});

    // 左下
    activeItem(acftLabel);
    activeItem(acftLatLabel);
    activeItem(acftLonLabel);
    activeItem(acftAltLabel);
    activeItem(acftYawLabel);
    activeItem(acftGSLabel);
    TextItemStyle(acftLabel, 16);
    acftLabel.setText("ACFT");
    acftLabel.setPos(-680, 350);
    TextItemStyle(acftLatLabel, 13);
    acftLatLabel.setText("N22 46.24");
    acftLatLabel.setPos(acftLabel.pos() + QPointF(80, 4));
    TextItemStyle(acftLonLabel, 13);
    acftLonLabel.setText("E55 3.32");
    acftLonLabel.setPos(acftLatLabel.pos() + QPointF(0, 35));
    TextItemStyle(acftAltLabel, 13);
    acftAltLabel.setText("300 ft");
    acftAltLabel.setPos(acftLonLabel.pos() + QPointF(0, 35));
    TextItemStyle(acftYawLabel, 13);
    acftYawLabel.setText("178deg");
    acftYawLabel.setPos(acftAltLabel.pos() + QPointF(0, 35));
    TextItemStyle(acftGSLabel, 13);
    acftGSLabel.setText("0kts");
    acftGSLabel.setPos(acftYawLabel.pos() + QPointF(0, 35));

    // 下
//    activeItem(rollIndicator);
//    activeItem(rollLabel);
    activeItem(OSS1Label);
    activeItem(OSS2Label);
    activeItem(OSS3Label);
    activeItem(OSS4Label);
    activeItem(OSS5Label);
    activeItem(OSS6Label);
    rollIndicator.setRadius(480);
    rollLabel.setText("0");
    rollLabel.setSize({40, 18});
    rollLabel.setPos(0, rollIndicator.radius() - 40);
    OSSStyle(OSS1Label);
    OSSStyle(OSS2Label);
    OSSStyle(OSS3Label);
    OSSStyle(OSS4Label);
    OSSStyle(OSS5Label);
    OSSStyle(OSS6Label);
    OSS1Label.setText("DISPLAY");
    OSS2Label.setText("SENSOR");
    OSS3Label.setText("FREEZ");
    OSS4Label.setText("MODES");
    OSS5Label.setText("SERVC");
    OSS6Label.setText("-----");
    OSS1Label.setPos(-75*2.5, 510);
    OSS2Label.setPos(-75*1.5, 510);
    OSS3Label.setPos(-75*0.5, 510);
    OSS4Label.setPos(75*0.5, 510);
    OSS5Label.setPos(75*1.5, 510);
    OSS6Label.setPos(75*2.5, 510);

    // 右下
    activeItem(tgtLabel);
    activeItem(tgtLatLabel);
    activeItem(tgtLonLabel);
    activeItem(tgtAltLabel);
    activeItem(tgtRangeLabel);
    activeItem(tgtKphLabel);
    TextItemStyle(tgtLabel, 16);
    tgtLabel.setText("TGT");
    tgtLabel.setPos(480, 350);
    TextItemStyle(tgtLatLabel, 13);
    tgtLatLabel.setText("N21 54.17");
    tgtLatLabel.setPos(tgtLabel.pos() + QPointF(60, 4));
    TextItemStyle(tgtLonLabel, 13);
    tgtLonLabel.setText("E55 21.74");
    tgtLonLabel.setPos(tgtLatLabel.pos() + QPointF(0, 35));
    TextItemStyle(tgtAltLabel, 13);
    tgtAltLabel.setText("251ft");
    tgtAltLabel.setPos(tgtLonLabel.pos() + QPointF(0, 35));
    TextItemStyle(tgtRangeLabel, 13);
    tgtRangeLabel.setText("1011740DTM");
    tgtRangeLabel.setPos(tgtAltLabel.pos() + QPointF(0, 35));
    TextItemStyle(tgtKphLabel, 13);
    tgtKphLabel.setPos(tgtRangeLabel.pos() + QPointF(0, 35));

    // 右右下
    activeItem(dateLabel);
    activeItem(timeLabel);
    activeItem(modeLabel);
    activeItem(laserLabel);
    TextItemStyle(dateLabel);
    dateLabel.setText("05.NOV.20");
    dateLabel.setPos(800, 370);
    TextItemStyle(timeLabel);
    timeLabel.setText("20:08:26");
    timeLabel.setPos(dateLabel.pos() + QPointF(0, 25));
    TextItemStyle(modeLabel);
    modeLabel.setText("MANUAL");
    modeLabel.setPos(timeLabel.pos() + QPointF(0, 25));
    laserLabel.setSize({80, 22});
    laserLabel.setPen({Qt::white});
    laserLabel.setBrush(Qt::NoBrush);
    laserLabel.setFont({"Microsoft Yahei", 15});
    laserLabel.setText("");
    laserLabel.setPos(780, 500);
    laserLabel.setBorder(Qt::NoPen);

    // 浮动
    activeItem(trackIndicator);
    activeItem(preTrackIndicator);
    activeItem(switchIndicator);
    switchIndicator.setPos(100, 100);

    // Invisible some items by default
    switchIndicator.setVisible(false);
    trackIndicator.setVisible(false);
    preTrackIndicator.setVisible(false);
    FGLIndicator.setVisible(false);
    FGLValueLabel.setVisible(false);
    FGLLabel.setVisible(false);
    laserIndicator.setVisible(false);
}
