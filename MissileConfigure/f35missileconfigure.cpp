#include "f35missileconfigure.h"
#include <QPainter>

F35MissileConfigure::F35MissileConfigure(QWidget *parent)
    : MissileConfigure(parent)
{
    m_path.moveTo(-55,0);
    m_path.lineTo(-58,65);
    m_path.lineTo(-70,90);
    m_path.lineTo(-170,160);
    m_path.lineTo(-170,220);
    m_path.lineTo(-58,248);
    m_path.lineTo(-70,270);
    m_path.lineTo(-118,305);
    m_path.lineTo(-118,335);
    m_path.lineTo(-32,350);
    m_path.lineTo(-20,285);
    m_path.lineTo(-12,300);
    m_path.lineTo(-0,300);

    for(int i = 0; i < 10; ++i) {
        this->setMissile(i, new EmptyMissile);
    }
}

void F35MissileConfigure::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setWindow(-180,0,360,360);

    QPen pen(m_painterColor,2);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(m_path);

    QTransform trans = painter.transform();
    painter.setTransform(trans.rotate(180,Qt::YAxis));

    painter.drawPath(m_path);
}

void F35MissileConfigure::resizeEvent(QResizeEvent *event)
{
    updateLayout();
}

QSize F35MissileConfigure::sizeHint() const
{
    return QSize(360,360);
}

void F35MissileConfigure::replaceMissie(int mount, Missile *curMissile)
{
    // 切换到下一个导弹
    switch (curMissile->property("Type").toInt()) {
        case Missile::Empty:
        {
            setMissile(mount, new InfraredMissile);
            break;
        }
        case Missile::Infrare:
        {
            setMissile(mount, new RadarMissile);
            break;
        }
        case Missile::Radar:
        {
            setMissile(mount, new EmptyMissile);
            break;
        }
    }
    updateLayout();
}

void F35MissileConfigure::updateLayout()
{
    QMapIterator<int, Missile*> iter(m_missileMap);
    while(iter.hasNext()) {
        auto item = iter.next();
        int mount = item.key();
        Missile *mis = iter.value();

        if(mount >= m_missileMap.size() / 2)
            mis->move(30 + mount * 25, 85);
        else
            mis->move(20 + mount * 25, 85);;
        mis->resize(24, 135);
    }
}
