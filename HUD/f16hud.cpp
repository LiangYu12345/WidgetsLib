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

void F16HUD::switcherMode(int mode)
{
    m_mode = mode;
    if(mode == 1){
        // 禁用其他模式的模块
        inactiveItem(m_missilereticle);
        inactiveItem(m_targetrange);
        inactiveItem(m_aim9missilediamond);
        inactiveItem(m_tdbox);
        inactiveItem(m_aamissiletype);
        inactiveItem(m_mlerange);
        inactiveItem(m_missilelaunchenvelope);
        inactiveItem(m_targetclosurerate);
        inactiveItem(m_prelaunchaim9timeofflight);
        inactiveItem(m_targetslantrange);
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
        m_maxgs.setValue(2.6f);

        activeItem(m_operatingmode);
        m_operatingmode.setPos(-440,330);
        m_operatingmode.setValue(u8"NAV");

        activeItem(m_machnumber);
        m_machnumber.setPos(-365,280);
        m_machnumber.setValue(0.88f);

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

        //中
        activeItem(m_leftlabelbeacon);
        m_leftlabelbeacon.setPos(-600,-80);
        m_leftlabelbeacon.setDirection(4);
        m_leftlabelbeacon.setValue(480);

        activeItem(m_leftlabelbeaconline);
        m_leftlabelbeaconline.setTextVisible(true);
        m_leftlabelbeaconline.setPos(-450,-80);

        activeItem(m_rightlabelbeacon);
        m_rightlabelbeacon.setPos(480,-80);
        m_rightlabelbeacon.setDirection(3);
        m_rightlabelbeacon.setValue(12500);

        activeItem(m_rightlabelbeaconline);
        m_rightlabelbeaconline.setTextVisible(false);
        m_rightlabelbeaconline.setPos(400,-80);

        //中下
        activeItem(m_rollindicator);
        m_rollindicator.setPos(0,100);
        m_rollindicator.setValue(0);

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

        // 俯仰 最上层
        activeItem(m_pitchattitudebars);
        m_pitchattitudebars.setPos(0,-50);
        m_pitchattitudebars.setValue(0);
        m_pitchattitudebars.setInclinationAngleValue(0);
    }
    else if(mode == 2){
        //禁用其他模式的模块
        inactiveItem(m_airspeedscales);
        inactiveItem(m_soisymbol);
        inactiveItem(m_currentg);
        inactiveItem(m_maxgs);
        inactiveItem(m_operatingmode);
        inactiveItem(m_machnumber);
        inactiveItem(m_masterarm);
        inactiveItem(m_bankangleindicator);
        inactiveItem(m_greatcirclesteeringcue);
        inactiveItem(m_steerpointsymbol);
        inactiveItem(m_leftlabelbeaconline);
        inactiveItem(m_rightlabelbeaconline);
        inactiveItem(m_rollindicator);
        inactiveItem(m_offsetaimpoint);
        inactiveItem(m_headingscale);
        inactiveItem(m_baroaltitudescales);
        inactiveItem(m_radaraltitude);
        inactiveItem(m_altitudelowsetting);
        inactiveItem(m_slantrange);
        inactiveItem(m_timetosteerpoint);
        inactiveItem(m_distancetosteerpoint);
        inactiveItem(m_pitchattitudebars);

        // 中
        activeItem(m_guncross);
        m_guncross.setPos(0,-400);

        activeItem(m_missilereticle);
        m_missilereticle.setPos(0,-150);

        activeItem(m_leftlabelbeacon);
        m_leftlabelbeacon.setPos(-600,-80);
        m_leftlabelbeacon.setDirection(4);
        m_leftlabelbeacon.setValue(480);

        activeItem(m_rightlabelbeacon);
        m_rightlabelbeacon.setPos(480,-80);
        m_rightlabelbeacon.setDirection(3);
        m_rightlabelbeacon.setValue(12500);

        activeItem(m_targetrange);
        m_targetrange.setPos(0,0);

        activeItem(m_flightpathmarker);
        m_flightpathmarker.setPos(0,100);

        //左
        activeItem(m_aim9missilediamond);
        m_aim9missilediamond.setPos(-350,-150);

        activeItem(m_tdbox);
        m_tdbox.setPos(0,0);

        //左下
        activeItem(m_aamissiletype);
        m_aamissiletype.setPos(-450,150);

        //右
        activeItem(m_mlerange);
        m_mlerange.setPos(450,-350);

        activeItem(m_missilelaunchenvelope);
        m_missilelaunchenvelope.setPos(460,-50);

        activeItem(m_targetclosurerate);
        m_targetclosurerate.setPos(380,0);

        //右下
        activeItem(m_prelaunchaim9timeofflight);
        m_prelaunchaim9timeofflight.setPos(450,150);

        activeItem(m_targetslantrange);
        m_targetslantrange.setPos(400,250);
    }
}

void F16HUD::initScene()
{
    auto scene = new QGraphicsScene;
    this->setScene(scene);
    // 综合考虑之后，将屏幕中心设置为坐标原点
    scene->setSceneRect(-1920/2, -1080/2, 1920, 1080);

    // 默认初始导航模式
    switcherMode(1);

//    QTimer *time = new QTimer;
//    connect(time,&QTimer::timeout,this,[=](){
//        m_mode ++;
//        if(m_mode > 2)
//            m_mode = 1;
//        switcherMode(m_mode);
//    });
//    time->start(5*1e3);
}
