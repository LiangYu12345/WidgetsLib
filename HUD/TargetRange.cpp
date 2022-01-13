#include "TargetRange.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

TargetRange::TargetRange()
{

}

void TargetRange::setValue(QString value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF TargetRange::boundingRect() const
{
    return QRectF();
}

void TargetRange::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(QPen(Qt::green));
    painter->setFont(QFont("Microsoft Yahei", 16));

    QFontMetricsF metrics(painter->font());
    auto textBound = metrics.boundingRect(m_value);
    //painter->drawText(QRectF(0, 0, textBound.width(), textBound.height()), Qt::AlignCenter, m_value);
}
