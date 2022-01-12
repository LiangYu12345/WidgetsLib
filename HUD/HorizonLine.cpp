#include "HorizonLine.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

HorizonLine::HorizonLine()
{

}

QRectF HorizonLine::boundingRect() const
{
    return QRectF(-960,-540,1920,1080);
}

void HorizonLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    QPen pen(Qt::gray);
    pen.setWidth(2);
    painter->setPen(pen);

    auto boundRect = boundingRect();
    auto w = boundRect.width();
    auto h = boundRect.height();
    painter->drawLine(-w,-40,-w/20,-40);
    painter->drawLine(w,-40,w/20,-40);
}
