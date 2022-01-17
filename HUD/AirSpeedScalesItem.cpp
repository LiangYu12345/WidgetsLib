#include "AirSpeedScalesItem.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

AirSpeedScalesItem::AirSpeedScalesItem()
{

}

void AirSpeedScalesItem::setRange(float range)
{
    if(m_range == range)
        return;
    m_range = qBound(100.0f, range, 500.0f);  //刻度尺范围最大
    update();
}

void AirSpeedScalesItem::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF AirSpeedScalesItem::boundingRect() const
{
    const qreal w = 80;
    const qreal h = m_pixPerDegree * m_range;
    return {-w/2, -h/2, w, h + 8};
}

void AirSpeedScalesItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(Qt::green);
    painter->setPen(QPen(Qt::green, 3));
    painter->setFont(QFont("Microsoft Yahei", 16));
    painter->setClipRect(boundingRect());
    float start = m_value - m_range / 2;
    float end = m_value + m_range / 2;

    start = int(start / 100) * 100;

    for(int i = start; i <= end; i += 10) {
        auto y = (m_value-i) * m_pixPerDegree;
        if(i % 50 == 0) {
            QFontMetricsF metrics(painter->font());
            auto temp = i / 10;
            QString text = QString::number(temp);
            auto textBound = metrics.boundingRect(text);
            painter->drawLine(0, y, m_lineWidth, y);
            if(i % 100 == 0)
            {
                if(i == m_value)
                    ;
                else
                    painter->drawText(QRectF(-m_textWidth, y-textBound.height()/2, m_textWidth, textBound.height()), Qt::AlignCenter, text);
            }
        }
        else
            painter->drawLine(m_lineWidth/2, y, m_lineWidth, y);
    }
}
