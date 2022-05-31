#include "HorizonLine.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

HorizonLine::HorizonLine()
{

}

void HorizonLine::setInclinationAngleValue(float value)
{
    m_angle = value;
}

QRectF HorizonLine::boundingRect() const
{
    return QRectF(-960,-540,1920,1080);
}

void HorizonLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

}
