#include "LabelBeacon.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

LabelBeacon::LabelBeacon()
{

}

void LabelBeacon::setValue(QString value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

void LabelBeacon::setDirection(int direction)
{
    if(m_direction == direction)
        return;
    m_direction = direction;
    update();
}

QRectF LabelBeacon::boundingRect() const
{
    if(m_direction == 1)
       return QRectF(-60,-50,120,100);
    else if(m_direction == 2)
       return QRectF(-60,-50,120,100);
    else if(m_direction == 3)
       return QRectF(-50,-60,100,120);
    else if(m_direction == 4)
       return QRectF(-50,-60,100,120);
}

void LabelBeacon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    auto boundRect = boundingRect();
    auto w = boundRect.width();
    auto h = boundRect.height();
    QPen pen(Qt::green);
    pen.setWidth(2);
    painter->setFont(QFont("Microsoft Yahei", 16));
    painter->setPen(pen);
    QPointF polygn[5];

    if(m_direction == 1)      // 1 上 2 下 3 左 4 右
    {
        polygn[0] = QPointF(w/3,h);
        polygn[1] = QPointF(w/3,h/8);
        polygn[2] = QPointF(w/2,0);
        polygn[3] = QPointF(w*2/3,h/8);
        polygn[4] =QPointF(w*2/3,h);
    }
    else if(m_direction == 2)
    {
        polygn[0] = QPointF(w/3,0);
        polygn[1] = QPointF(w/3,h*7/8);
        polygn[2] = QPointF(w/2,h);
        polygn[3] = QPointF(w*2/3,0);
        polygn[4] =QPointF(w*2/3,h*7/8);
    }
    else if(m_direction == 3)
    {
        polygn[0] = QPointF(w,h/3);
        polygn[1] = QPointF(w/8,h/3);
        polygn[2] = QPointF(0,h/2);
        polygn[3] = QPointF(w/8,h*2/3);
        polygn[4] =QPointF(w,h*2/3);
    }
    else if(m_direction == 4)
    {
        polygn[0] = QPointF(0,h/3);
        polygn[1] = QPointF(w*7/8,h/3);
        polygn[2] = QPointF(w,h/2);
        polygn[3] = QPointF(w*7/8,h*2/3);
        polygn[4] =QPointF(0,h*2/3);
    }

    painter->drawPolygon(polygn,5);

    QFontMetricsF metrics(painter->font());
    auto textBound = metrics.boundingRect(m_value);
    painter->drawText(QRectF(20, h/2 - textBound.height()/2, textBound.width(), textBound.height()), Qt::AlignCenter, m_value);
}
