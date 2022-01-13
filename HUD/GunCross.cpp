#include "GunCross.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

GunCross::GunCross()
{

}

QRectF GunCross::boundingRect() const
{
    return QRectF();
}

void GunCross::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    QPen pen(Qt::green);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawLine(-m_lineWidth,0,-m_lineWidth/5,0);
    painter->drawLine(m_lineWidth/5,0,m_lineWidth,0);
    painter->drawLine(0,m_lineWidth,0,m_lineWidth/5);
    painter->drawLine(0,-m_lineWidth/5,0,-m_lineWidth);
}
