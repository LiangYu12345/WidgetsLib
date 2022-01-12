#include "FlightPathMarker.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

FlightPathMarker::FlightPathMarker()
{

}

QRectF FlightPathMarker::boundingRect() const
{
    return QRectF(-20,-20,40,40);
}

void FlightPathMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::green);
    painter->setPen(pen);
    auto boundRect = boundingRect();
    auto w = boundRect.width();
    auto h = boundRect.height();

    painter->drawLine(-w,h/2,-w/3,h/2);
    painter->drawLine(0,0,0,h/4);
    painter->drawLine(w,h/2,w/3,h/2);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawEllipse(QRectF(-w/4,h/4,w/2,h/2));
}
