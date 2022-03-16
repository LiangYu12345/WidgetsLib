#include "j20weaponconfigure.h"
#include <QPainter>

J20WeaponConfigure::J20WeaponConfigure(QWidget *parent)
    :MissileConfigure(parent)
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

void J20WeaponConfigure::replaceMissie(int mount, Missile *curMissile)
{
    return;
}
