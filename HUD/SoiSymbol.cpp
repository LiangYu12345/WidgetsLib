#include "SoiSymbol.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

SoiSymbol::SoiSymbol()
{

}

void SoiSymbol::setVisible(bool visible)
{
    if(m_visible == visible)
        return;
    m_visible = visible;
    update();
}

QRectF SoiSymbol::boundingRect() const
{
    return QRectF(-5,-5,10,10);
}

void SoiSymbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QPen pen(Qt::green);
    pen.setWidth(2);
    painter->setPen(pen);

    if(m_visible)
    {
        painter->drawLine(-m_lineWidth/2,0,m_lineWidth/2,0);
        painter->drawLine(0,m_lineWidth/2,0,-m_lineWidth/2);
        painter->drawLine(-m_lineWidth/3,m_lineWidth/3,m_lineWidth/3,-m_lineWidth/3);
        painter->drawLine(-m_lineWidth/3,-m_lineWidth/3,m_lineWidth/3,m_lineWidth/3);
    }
}
