#include "TargetSlantRange.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

TargetSlantRange::TargetSlantRange()
{

}

void TargetSlantRange::setValueFirst(QString value)
{
    if(m_valuefirst == value)
        return;
    m_valuefirst = value;
    update();
}

void TargetSlantRange::setValueSecond(QString value)
{
    if(m_valuesecond == value)
        return;
    m_valuesecond = value;
    update();
}

void TargetSlantRange::setValueThird(QString value)
{
    if(m_valuethird == value)
        return;
    m_valuethird = value;
    update();
}

QRectF TargetSlantRange::boundingRect() const
{
    return QRectF();
}

void TargetSlantRange::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(QPen(Qt::green));
    painter->setFont(QFont("Microsoft Yahei", 16));

    QFontMetricsF metrics(painter->font());
    auto textBoundfirst = metrics.boundingRect(m_valuefirst);
    painter->drawText(QRectF(0, 0, textBoundfirst.width(), textBoundfirst.height()), Qt::AlignCenter, m_valuefirst);
    auto textBoundsecond = metrics.boundingRect(m_valuesecond);
    painter->drawText(QRectF(0, textBoundfirst.height(), textBoundsecond.width(), textBoundsecond.height()), Qt::AlignCenter, m_valuesecond);
    auto textBoundthird = metrics.boundingRect(m_valuethird);
    painter->drawText(QRectF(0, textBoundfirst.height() + textBoundsecond.height(), textBoundthird.width(), textBoundthird.height()), Qt::AlignCenter, m_valuethird);
}
