#include "MissileReticle.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

MissileReticle::MissileReticle()
{

}

void MissileReticle::setValue(QString value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF MissileReticle::boundingRect() const
{
    return QRectF(-200,-200,400,400);
}

void MissileReticle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    auto boundRect = boundingRect();
    auto w = boundRect.width();
    auto h = boundRect.height();

    painter->setPen(QPen(Qt::green,2));
    painter->setFont(QFont("Microsoft Yahei", 16));

    painter->save();
    painter->rotate(-55);
    painter->setBrush(Qt::green);
    QPointF triangle[3] = {               //   0-360
        QPointF(-m_lineWidth / 4, -h/2 - m_lineWidth / 2),
        QPointF(m_lineWidth / 4, -h/2 - m_lineWidth / 2),
        QPointF(0, -h/2)
    };
    painter->drawPolygon(triangle, 3);

    painter->setPen(QPen(Qt::green,4));
    painter->rotate(-20);
    painter->drawLine(0,-h/2,0,-h/2+m_lineWidth);

    painter->restore();

    painter->drawEllipse(QRectF(-w/2,-h/2,w,h));
    painter->drawLine(0,-h/2 - 10,0,-h/2 + 10);
    painter->drawLine(-w/2 -10,0,-w/2,0);
    painter->drawLine(0,h/2,0,h/2 + 10);
    painter->drawLine(w/2,0,w/2+10,0);


}
