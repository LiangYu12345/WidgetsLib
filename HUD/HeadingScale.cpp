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
    const float w = m_pixPerDegree * m_range + 22;
    const float h = 100;
    return {-w/2, -50, w, h};
}

void HeadingScale::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::green, 3));
    painter->setFont(QFont("Microsoft Yahei", 16));
    painter->setClipRect(boundingRect());
    painter->translate(-m_value * m_pixPerDegree, 0);
    int start = m_value - m_range / 2;
    int end = m_value + m_range / 2;
    for(int i = start; i <= end; i+=5) {
        int value = i;
        if(value < 0)\


            value += 360;
        else if(value > 360)
            value -= 360;
        auto x = i * m_pixPerDegree;
        if(value % 10 == 0) {
            QFontMetricsF metrics(painter->font());
            QString text =QString("0")+QString::number(value);
            auto textBound = metrics.boundingRect(text);
            painter->drawLine(x, 0, x, m_lineHeight);
            if(m_value == value)
            {
                painter->drawRect(QRectF({x - textBound.width()/2 - 5, m_textHeight/2}, textBound.size() + QSize(10,0)));
                painter->drawText(QRectF({x - textBound.width()/2 - 5, m_textHeight/2}, textBound.size() + QSize(10,0)), Qt::AlignHCenter|Qt::AlignBottom, text);
            }
            else {
                QString text =QString::number(value);
                auto textBound = metrics.boundingRect(text);
                painter->drawText(QRectF({x - textBound.width()/2, m_textHeight/2}, textBound.size()), Qt::AlignHCenter|Qt::AlignBottom, text);
            }
        }
        else
            painter->drawLine(x, 0, x, m_lineHeight / 2);
    }
}
