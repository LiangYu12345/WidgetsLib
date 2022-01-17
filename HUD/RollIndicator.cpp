#include "RollIndicator.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

f16RollIndicator::f16RollIndicator()
{

}

void f16RollIndicator::setRange(float range)
{
    if(m_range == range)
        return;
    m_range = qBound(100.0f, range, 500.0f);
    update();
}

void f16RollIndicator::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

void f16RollIndicator::setRadius(float radius)
{
    if(m_radius == radius)
        return;
    m_radius = radius;
    update();
}

const float &f16RollIndicator::radius() const
{
    return m_radius;
}

QRectF f16RollIndicator::boundingRect() const
{
    return {-m_radius, 0, m_radius * 2, m_radius*1.1};
}
void f16RollIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(Qt::green);
    painter->setPen(QPen(Qt::green, 2));
    painter->setClipRect(boundingRect());
    float start = m_value - m_range/2;
    float end = m_value + m_range/2;
    start = int(start / 5) * 5;
    painter->save();
    painter->rotate(start - m_value);
    for(int i = start; i <= end; i+=10) {
        if(i % 20 == 0)
            painter->drawLine(0, m_radius, 0, m_radius - m_lineLen);
        else
            painter->drawLine(0, m_radius-m_lineLen/2, 0, m_radius - m_lineLen);
        painter->rotate(10);
    }
    painter->restore();
    const float xDelta = m_lineLen / 4;
    const float yLen = m_lineLen / 2;
    QPointF triangle[3] = {
        QPointF(0, m_radius),
        QPointF(-xDelta, m_radius+yLen),
        QPointF(xDelta, m_radius+yLen)
    };
    painter->drawPolygon(triangle, 3);
}
