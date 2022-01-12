#include "HeadingScale.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

HeadingScale::HeadingScale()
{

}

void HeadingScale::setRange(float range)
{
    if(m_range == range)
        return;
    m_range = qBound(5.0f, range, 20.0f);
    update();
}

void HeadingScale::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF HeadingScale::boundingRect() const
{
    const float w = m_pixPerDegree * m_range;
    const float h = m_lineHeight + m_textHeight;
    return {-w/2, -m_textHeight, w, h};
}

void HeadingScale::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(Qt::green);
    painter->setPen(QPen(Qt::green, 3));
    painter->setFont(QFont("Microsoft Yahei", 16));
    painter->setClipRect(boundingRect());
    painter->translate(-m_value * m_pixPerDegree, 0);
    int start = m_value - m_range / 2;
    int end = m_value + m_range / 2;
    for(int i = start; i <= end; i+=5) {
        int value = i;
        if(value < 0)
            value += 360;
        else if(value > 360)
            value -= 360;
        auto x = i * m_pixPerDegree;
        if(value % 10 == 0) {
            QFontMetricsF metrics(painter->font());
            QString text = QString::number(value);
            auto textBound = metrics.boundingRect(text);
            painter->drawLine(x, 0, x, m_lineHeight);
            painter->drawText(QRectF({x - textBound.width()/2, -m_textHeight}, textBound.size()), Qt::AlignHCenter|Qt::AlignBottom, text);
        }
        else
            painter->drawLine(x, m_lineHeight/2, x, m_lineHeight);
    }
}
