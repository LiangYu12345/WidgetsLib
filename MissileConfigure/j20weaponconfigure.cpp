#include "j20weaponconfigure.h"
#include <QPainter>
#include <QDebug>

J20WeaponConfigure::J20WeaponConfigure(QWidget *parent)
    :WeaponConfigure(parent)
{
    m_path.moveTo(0,0);
    m_path.cubicTo(QPointF(-0,0),QPointF(-0,-10),QPointF(-5,10));
    m_path.cubicTo(QPointF(-15,30),QPointF(-20,150),QPointF(-20,159));
    m_path.lineTo(-30,180);
    m_path.lineTo(-40,171);
    m_path.lineTo(-50,195);
    m_path.lineTo(-98,243);
    m_path.lineTo(-100,268);
    m_path.lineTo(-50,261);
    m_path.lineTo(-60,330);
    m_path.lineTo(-170,465);
    m_path.lineTo(-170,505);
    m_path.lineTo(-78,523);
    m_path.lineTo(-87,534);
    m_path.lineTo(-93,570);
    m_path.lineTo(-63,552);
    m_path.lineTo(-60,573);
    m_path.lineTo(-51,573);
    m_path.lineTo(-45,530);
    m_path.lineTo(-23,562);
    m_path.lineTo(-9,562);
    m_path.lineTo(-4,532);
    m_path.lineTo(0,537);
}

void J20WeaponConfigure::paintEvent(QPaintEvent *e)
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

void J20WeaponConfigure::resizeEvent(QResizeEvent *event)
{

}

QSize J20WeaponConfigure::sizeHint() const
{
    return QSize(360,580);
}

void J20WeaponConfigure::mouseDoubleClickEvent(QMouseEvent *e)
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

// 判断点是否在矩形内部
// 判断一个点是否在某条线段的一边上，就可以利用叉乘的方向性，来判断夹角是否超过了180度
bool J20WeaponConfigure::isPointInMatrix(QPointF p1, QPointF p2, QPointF p3, QPointF p4, QPointF p)
{
    return getCross(p1,p2,p) * getCross(p3,p4,p) >= 0 && getCross(p2,p3,p) * getCross(p4,p1,p) >= 0;
}

double J20WeaponConfigure::getCross(QPointF p1, QPointF p2, QPointF p)
{
    return ((p2.x() - p1.x()) * (p.y() - p1.y())) - ((p.x() - p1.x()) * (p2.y() - p1.y()));
}
