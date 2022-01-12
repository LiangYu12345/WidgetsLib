#include "MachNumber.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

MachNumber::MachNumber()
{

}

void MachNumber::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF MachNumber::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

void MachNumber::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(QPen(Qt::green));
    painter->setFont(QFont("Microsoft Yahei", 16));
    QFontMetricsF metrics(painter->font());
    QString text = QString::number(m_value);
    auto textBound = metrics.boundingRect(text);
    painter->drawText(QRectF(-m_textWidth, -textBound.height()/2, m_textWidth, textBound.height()), Qt::AlignCenter, QString::number(m_value));
}
