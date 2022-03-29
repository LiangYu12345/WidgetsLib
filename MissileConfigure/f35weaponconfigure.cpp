#include "f35weaponconfigure.h"
#include <QPainter>

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

void F35WeaponConfigure::resizeEvent(QResizeEvent *e)
{
}

QSize F35WeaponConfigure::sizeHint() const
{
    return QSize(360,580);
}

void F35WeaponConfigure::replaceMissie(int mount, Missile *curMissile)
{
    return;
}

void F35WeaponConfigure::mouseDoubleClickEvent(QMouseEvent *e)
{
    auto point = e->pos();
    auto weaponSize = QSize(40,40);
    auto weaponWith = weaponSize.width();
    auto weaponHeight = weaponSize.height();
    if(m_weaponMap.isEmpty()){
        WeaponSpace weapon;
        weapon.position = point - QPointF(weaponWith/2, weaponHeight/2);
        weapon.size = weaponSize;
        weapon.xx = new XXWeapon(this);
        weapon.xx->move(point.x() - weaponWith/2,point.y() - weaponHeight/2);
        this->setWeapon(0, weapon);
        weapon.xx->show();
        m_weaponMap.insert(0,weapon);
    }
    else{
        QMapIterator<int, WeaponSpace> iter(m_weaponMap);
        while(iter.hasNext()){
            auto item = iter.peekNext().value();
            auto p1 = item.position;
            QPointF p2 = {item.position.x() + item.size.width(),item.position.y()};
            QPointF p4 = {item.position.x(),item.position.y() + item.size.height()};
            QPointF p3 = {item.position.x() + item.size.width(),item.position.y() + item.size.height()};
            auto p = point;
            if(isPointInMatrix(p1,p2,p3,p4,p)){
                return;
            }
            iter.next();
        }
        auto weaponCount = m_weaponMap.size();
        WeaponSpace weapon;
        weapon.position = point - QPointF(weaponWith/2, weaponHeight/2);
        weapon.size = weaponSize;
        weapon.xx = new XXWeapon(this);
        this->setWeapon(weaponCount, weapon);
        weapon.xx->show();
        weapon.xx->move(point.x() - weaponWith/2,point.y() - weaponHeight/2);
        m_weaponMap.insert(weaponCount,weapon);
    }
}

bool F35WeaponConfigure::isPointInMatrix(QPointF p1, QPointF p2, QPointF p3, QPointF p4, QPointF p)
{
    return getCross(p1,p2,p) * getCross(p3,p4,p) >= 0 && getCross(p2,p3,p) * getCross(p4,p1,p) >= 0;
}

double F35WeaponConfigure::getCross(QPointF p1, QPointF p2, QPointF p)
{
    return ((p2.x() - p1.x()) * (p.y() - p1.y())) - ((p.x() - p1.x()) * (p2.y() - p1.y()));
}
