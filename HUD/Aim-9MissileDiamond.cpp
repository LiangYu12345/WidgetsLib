#include "Aim-9MissileDiamond.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

Aim9MissileDiamond::Aim9MissileDiamond()
{

}

void Aim9MissileDiamond::setValue(QString value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF Aim9MissileDiamond::boundingRect() const
{
    return QRectF(-30,-30,60,60);
}

void Aim9MissileDiamond::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(QPen(Qt::green,2));
    painter->setFont(QFont("Microsoft Yahei", 16));

    auto boundRect = boundingRect();
    auto w = boundRect.width();
    auto h = boundRect.height();

    //QFontMetricsF metrics(painter->font());
    //auto textBound = metrics.boundingRect(m_value);

    painter->drawRect(-w/2,-h/2,w,h);
    painter->save();
    painter->rotate(45);
    painter->drawRect(-w*2/3/2,-h*2/3/2,w*2/3,h*2/3);
    painter->restore();
}
