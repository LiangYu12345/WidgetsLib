#include "DistanceToSteerpoint.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

DistanceToSteerpoint::DistanceToSteerpoint()
{

}

void DistanceToSteerpoint::setValue(QString value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

void DistanceToSteerpoint::setDisToValue(QString value)
{
    if(m_distovalue == value)
        return;
    m_distovalue = value;
    update();
}

QRectF DistanceToSteerpoint::boundingRect() const
{
    return QRectF();
}

void DistanceToSteerpoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::green));
    painter->setFont(QFont("Microsoft Yahei", 16));
    QFontMetricsF metrics(painter->font());
    auto textBound = metrics.boundingRect(m_distovalue);
    painter->drawText(QRectF(0, 0, textBound.width(), textBound.height()), Qt::AlignCenter, m_distovalue);

    QPen pen(4);
    pen.setColor(Qt::green);
    painter->setPen(pen);
    painter->drawLine(textBound.width() + 10,textBound.height()/4,textBound.width() + 20,textBound.height()/2);
    painter->drawLine(textBound.width() + 10,textBound.height()*3/4,textBound.width() + 20,textBound.height()/2);

    auto distotextBound = metrics.boundingRect(m_value);
    painter->drawText(QRectF(textBound.width() + 30, 0, distotextBound.width(), distotextBound.height()), Qt::AlignCenter, m_value);

}
