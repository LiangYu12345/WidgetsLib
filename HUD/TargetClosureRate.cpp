#include "TargetClosureRate.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

TargetClosureRate::TargetClosureRate()
{

}

void TargetClosureRate::setValue(double value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF TargetClosureRate::boundingRect() const
{
    return QRectF();
}

void TargetClosureRate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(QPen(Qt::green,2));
    painter->setFont(QFont("Microsoft Yahei", 16));

    QFontMetricsF metrics(painter->font());
    auto textBound = metrics.boundingRect(QString::number(m_value));
    painter->drawText(QRectF(0, 0, textBound.width(), textBound.height()), Qt::AlignCenter, QString::number(m_value));

    painter->drawLine(textBound.width() + 10,textBound.height()/4,textBound.width() + 20,textBound.height()/2);
    painter->drawLine(textBound.width() + 10,textBound.height()*3/4,textBound.width() + 20,textBound.height()/2);
}




