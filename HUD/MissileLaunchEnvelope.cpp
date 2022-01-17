#include "MissileLaunchEnvelope.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

MissileLaunchEnvelope::MissileLaunchEnvelope()
{

}

void MissileLaunchEnvelope::setValue(QString value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF MissileLaunchEnvelope::boundingRect() const
{
    return QRectF(-25,-100,50,200);
}

void MissileLaunchEnvelope::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    auto boundRect = boundingRect();
    auto w = boundRect.width();
    auto h = boundRect.height();

    painter->setPen(QPen(Qt::green));
    painter->setFont(QFont("Microsoft Yahei", 16));

    QFontMetricsF metrics(painter->font());
    auto textBound = metrics.boundingRect(m_value);

    painter->setPen(QPen(Qt::green,4));
    painter->drawLine(-m_lineWidth/4,-h/2,m_lineWidth/4,-h/2);
    painter->drawLine(-m_lineWidth/4,h/2,m_lineWidth/4,h/2);

    painter->setPen(QPen(Qt::green,2));
    painter->drawLine(-m_lineWidth/4,-h/2,-m_lineWidth/4,h/2);
    painter->drawLine(-m_lineWidth/4,-h/4,m_lineWidth/4,-h/4);
    painter->drawLine(m_lineWidth/4,-h/4,m_lineWidth/4,h/3);
    painter->drawLine(-m_lineWidth/4,h/3,m_lineWidth/4,h/3);
}
