#include "f35weaponconfigure.h"
#include <QPainter>

#include "xxweapon.h"

F35WeaponConfigure::F35WeaponConfigure(QWidget * parent)
    :MissileConfigure(parent)
{
    m_path.moveTo(0,0);
    m_path.cubicTo(QPointF(-0,0),QPointF(-0,-5),QPointF(-10,20));
    m_path.cubicTo(QPointF(-15,30),QPointF(-25,150),QPointF(-25,159));
    m_path.lineTo(-35,180);
    m_path.lineTo(-50,159);
    m_path.lineTo(-55,171);
    m_path.lineTo(-58,290);
    m_path.lineTo(-70,315);
    m_path.lineTo(-170,385);
    m_path.lineTo(-170,445);
    m_path.lineTo(-58,473);
    m_path.lineTo(-70,495);
    m_path.lineTo(-118,530);
    m_path.lineTo(-118,560);
    m_path.lineTo(-32,575);
    m_path.lineTo(-20,510);
    m_path.lineTo(-12,525);
    m_path.lineTo(-0,525);

    for(int nIndex = 0; nIndex < 6; ++nIndex){
        auto xxweapon = new XXWeapon(this);
        m_weaponMap.insert(nIndex,xxweapon);
    }
}

void F35WeaponConfigure::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setWindow(-180,0,360,580);

    QPen pen(m_painterColor,2);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(m_path);

    QTransform trans = painter.transform();
    painter.setTransform(trans.rotate(180,Qt::YAxis));

    painter.drawPath(m_path);
}

void F35WeaponConfigure::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton){
        //if()
        e->pos();
    }
}

void F35WeaponConfigure::resizeEvent(QResizeEvent *e)
{
    updateLayout();
}

QSize F35WeaponConfigure::sizeHint() const
{
    return QSize(360,580);
}

void F35WeaponConfigure::replaceMissie(int mount, Missile *curMissile)
{
    return;
}

void F35WeaponConfigure::updateLayout()
{
    QMapIterator<int, XXWeapon*> iter(m_weaponMap);
    while(iter.hasNext()) {
        auto item = iter.next();
        int mount = item.key();
        XXWeapon *weapon = iter.value();

        //weapon->move(40 + mount * 40, 250);
        weapon->resize(40, 40);
    }
}
