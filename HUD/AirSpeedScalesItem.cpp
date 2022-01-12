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
    const float w = m_lineWidth + m_textWidth;
    const float h = m_pixPerDegree * m_range;
    return {-m_textWidth, -h/2, w, h};       //-40 -200 60 400 //-40 -160 60 320
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
    // clamp start to 10 times like as 10 20 30 etc
    for(int i = start; i <= end; i++) {
        auto y = (m_value-i) * m_pixPerDegree;
        if(i % 10 == 0) {
            QFontMetricsF metrics(painter->font());
            QString text = QString::number(i);
            auto textBound = metrics.boundingRect(text);
            painter->drawLine(0, y, m_lineWidth, y);
            painter->drawText(QRectF(-m_textWidth, y-textBound.height()/2, m_textWidth, textBound.height()), Qt::AlignCenter, text);
        }
        else if(i % 5 == 0)
        {
            painter->drawLine(0, y, m_lineWidth, y);
        }
        else
            painter->drawLine(m_lineWidth/2, y, m_lineWidth, y);
    }
}
