#include "j20missileconfigure.h"
#include "emptymissile.h"
#include "infraredmissile.h"
#include <QPainter>

J20MissileConfigure::J20MissileConfigure(QWidget *parent)
    : MissileConfigure(parent)
{
    m_path.moveTo(-80,0);
    m_path.lineTo(-98, 18);
    m_path.lineTo(-100, 43);
    m_path.lineTo(-50,36);
    m_path.lineTo(-60,105);
    m_path.lineTo(-170,240);
    m_path.lineTo(-170,280);
    m_path.lineTo(-78,298);
    m_path.lineTo(-87,309);
    m_path.lineTo(-93,345);
    m_path.lineTo(-63,327);
    m_path.lineTo(-60,348);
    m_path.lineTo(-51,348);
    m_path.lineTo(-45,305);
    m_path.lineTo(-23,337);
    m_path.lineTo(-9,337);
    m_path.lineTo(-4, 307);
    m_path.lineTo(0,312);

    for(int i = 0; i < 6; ++i) {
        this->setMissile(i, new EmptyMissile);
    }
}

void J20MissileConfigure::paintEvent(QPaintEvent *e)
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

void J20MissileConfigure::resizeEvent(QResizeEvent *event)
{
    updateLayout();
}

QSize J20MissileConfigure::sizeHint() const
{
    return QSize(360,360);
}

void J20MissileConfigure::replaceMissie(int mount, Missile *curMissile)
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

void J20MissileConfigure::updateLayout()
{
    QMapIterator<int, Missile*> iter(m_missileMap);
    while(iter.hasNext()) {
        auto item = iter.next();
        int mount = item.key();
        Missile *mis = iter.value();

        mis->move(40 + mount * 40, 100);
        mis->resize(24, 135);
    }
}
