#include "OffsetAimpoint.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

OffsetAimpoint::OffsetAimpoint()
{

}

QRectF OffsetAimpoint::boundingRect() const
{
    return QRectF(-10,-10,10,30);
}

void OffsetAimpoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    const auto rect = boundingRect();
    const auto height_2 = rect.height()/2;
    const auto width_2 = rect.width()/2;
    QPointF triangle[3] = {
        {-width_2, height_2},
        {width_2, height_2},
        {0, -height_2}
    };
    QPen pen(Qt::green);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawPolygon(triangle, 3);
}
