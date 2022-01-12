#include "BankAngleIndicator.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

BankAngleIndicator::BankAngleIndicator()
{

}

void BankAngleIndicator::setRange(float range)
{
    if(m_range == range)
        return;
    m_range = range;
    update();
}

void BankAngleIndicator::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

void BankAngleIndicator::setRadius(float radius)
{
    if(m_radius == radius)
        return;
    m_radius = radius;
    update();
}

QRectF BankAngleIndicator::boundingRect() const
{
    //return {-m_radius, 0, m_radius * 2, m_radius*1.1};
    return QRectF(-200,-200,400,400);
}

void BankAngleIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(Qt::green);
    painter->setPen(QPen(Qt::green, 2));
    painter->setClipRect(boundingRect());
    float start = m_value - m_range/2;
    float end = m_value + m_range/2;
    start = int(start / 10) * 10;
    painter->save();                      //旋转-60  60°
    painter->rotate(start - m_value +180);   //默认旋转-40° 40°
    for(int i = start; i <= end; i+=10) {
        if(i % 30 == 0)
            painter->drawLine(0, m_radius, 0, m_radius - m_lineLen);
        else if(i <=20 && i>=-20)
            painter->drawLine(0,m_radius - m_lineLen/2,0,m_radius - m_lineLen);
        else
            ;
        painter->rotate(10);
    }
    painter->restore();
}
