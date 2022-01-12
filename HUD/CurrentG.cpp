#include "CurrentG.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

CurrentG::CurrentG()
{

}

void CurrentG::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF CurrentG::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

void CurrentG::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->setBrush(Qt::green);
    painter->setPen(QPen(Qt::green, 3));
    painter->setFont(QFont("Microsoft Yahei", 16));
    QFontMetricsF metrics(painter->font());
    QString text = QString::number(double(m_value), 'f', 1);
    auto textBound = metrics.boundingRect(text);
    painter->drawText(QRectF(-m_textWidth, -textBound.height()/2, m_textWidth, textBound.height()), Qt::AlignCenter, text);
}
