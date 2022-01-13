#include "BaroAltitudeScales.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

BaroAltitudeScales::BaroAltitudeScales()
{

}

void BaroAltitudeScales::setRange(float range)
{
    if(m_range == range)
        return;
    m_range = qBound(100.0f, range, 500.0f);
    update();
}

void BaroAltitudeScales::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF BaroAltitudeScales::boundingRect() const
{
    const float w = 80;
    const float h = m_pixPerDegree * m_range;
    return {-m_lineWidth, -h/2, w, h};
}

void BaroAltitudeScales::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    for(int i = start; i <= end; i+= 100) {
        auto y = (m_value-i) / m_pixPerDegree;
        if(i % 500 == 0) {
            QFontMetricsF metrics(painter->font());
            auto temp = i / 100;
            auto front = temp/10;
            auto back = temp % 10;

            QString text = QString("%1,%2").arg(front).arg(back);
            auto textBound = metrics.boundingRect(text);
            painter->drawLine(-m_lineWidth, y, 0, y);
            if(m_value == i)
                ;
            else
                painter->drawText(QRectF(textBound.width() /4, y -textBound.height()/2, textBound.width(), textBound.height()), Qt::AlignCenter, text);
        }
        else
            painter->drawLine(-m_lineWidth, y, -m_lineWidth/2, y);
    }
}
