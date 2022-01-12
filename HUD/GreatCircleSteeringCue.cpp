#include "GreatCircleSteeringCue.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

GreatCircleSteeringCue::GreatCircleSteeringCue()
{

}

QRectF GreatCircleSteeringCue::boundingRect() const
{
    return QRectF(-15,-15,20,20);
}

void GreatCircleSteeringCue::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    auto boundRect = boundingRect();
    auto w = boundRect.width();
    auto h = boundRect.height();

    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(1);
    painter->setPen(pen);

    painter->drawLine(0,-h/4,w/4,-h);

    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawEllipse(-w/4,-h/4,w/2,h/2);
}
