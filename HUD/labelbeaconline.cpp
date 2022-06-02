#include "labelbeaconline.h"
#include <QPainter>

LabelBeaconLine::LabelBeaconLine()
{
    m_text = "C";
}

void LabelBeaconLine::setTextVisible(bool visible)
{
    m_visible = visible;
}

void LabelBeaconLine::setText(QString str)
{
    m_text = str;
}

QRectF LabelBeaconLine::boundingRect() const
{
    return QRectF(-20,-30,40,60);
}

void LabelBeaconLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    auto boundRect = boundingRect();
    auto w = boundRect.width();
    auto h = boundRect.height();
    QPen pen(Qt::green);
    pen.setWidth(3);
    painter->setFont(QFont("Microsoft Yahei", 22));
    painter->setPen(pen);

    QFontMetricsF metrics(painter->font());
    auto textBound = metrics.boundingRect(m_text);
    if(m_visible)
        painter->drawText(QRectF(0, h/2 - textBound.height()/2, textBound.width(), textBound.height()), Qt::AlignCenter, m_text);

    painter->drawLine(0,h,40,h);

}
