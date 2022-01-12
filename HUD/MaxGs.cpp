#include "MaxGs.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

MaxGs::MaxGs()
{

}

void MaxGs::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF MaxGs::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

void MaxGs::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(QPen(Qt::green));
    painter->setFont(QFont("Microsoft Yahei", 16));
    QFontMetricsF metrics(painter->font());
    QString text = QString::number(m_value);
    auto textBound = metrics.boundingRect(text);
    painter->drawText(QRectF(0, 0, textBound.width(), textBound.height()), Qt::AlignCenter, QString::number(m_value));
}
