#include "MleRange.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

MleRange::MleRange()
{

}

void MleRange::setValue(double value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF MleRange::boundingRect() const
{
    return QRectF();
}

void MleRange::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(QPen(Qt::green));
    painter->setFont(QFont("Microsoft Yahei", 16));

    QFontMetricsF metrics(painter->font());
    auto textBound = metrics.boundingRect(QString::number(m_value));
    painter->drawText(QRectF(0, 0, textBound.width(), textBound.height()), Qt::AlignCenter, QString::number(m_value));
    painter->drawLine(0,textBound.height(),textBound.width(),textBound.height());
}
