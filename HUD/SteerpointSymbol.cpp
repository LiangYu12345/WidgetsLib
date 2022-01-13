#include "SteerpointSymbol.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

SteerpointSymbol::SteerpointSymbol()
{

}

QRectF SteerpointSymbol::boundingRect() const
{
    return QRectF(-7,-7,14,14);
}

void SteerpointSymbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const auto boundRect = boundingRect();
    auto w = boundRect.width();
    auto h = boundRect.height();

    QPen pen(Qt::green);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->save();

    painter->rotate(45);
    painter->drawRect(-w/2,-h/2,w,h);
    painter->restore();
}
