#include "TargetAspect.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

TargetAspect::TargetAspect()
{

}

void TargetAspect::setValue(QString value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF TargetAspect::boundingRect() const
{
    return QRectF();
}

void TargetAspect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(QPen(Qt::green,2));
    painter->setBrush(Qt::green);
    painter->setFont(QFont("Microsoft Yahei", 16));

//    QFontMetricsF metrics(painter->font());
//    auto textBound = metrics.boundingRect(m_value);

    const float xDelta = m_lineLen / 4;
    const float yLen = m_lineLen / 2;
    QPointF triangle[3] = {
        QPointF(0, m_radius),
        QPointF(-xDelta, m_radius+yLen),
        QPointF(xDelta, m_radius+yLen)
    };
    painter->drawPolygon(triangle, 3);
}
