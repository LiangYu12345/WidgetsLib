#include "RadarAltitude.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

RadarAltitude::RadarAltitude()
{

}

void RadarAltitude::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF RadarAltitude::boundingRect() const
{
    return QRectF(-30,-10,50,20);
}

void RadarAltitude::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(QPen(Qt::green));
    painter->setFont(QFont("Microsoft Yahei", 16));
    QFontMetricsF metrics(painter->font());
    QString text = QString(u8" R ");
    auto textBound = metrics.boundingRect(text);
    painter->drawText(QRectF(0, 0, textBound.width(), textBound.height()), Qt::AlignCenter, text);

    QString valuetext = QString::number(m_value);
    auto valuetextBound = metrics.boundingRect(valuetext);
    painter->drawText(QRectF(textBound.width() + 20, 0, valuetextBound.width(), valuetextBound.height()), Qt::AlignCenter, QString::number(m_value));

    painter->drawRect(textBound.width() + 10,0,valuetextBound.width() + 20, valuetextBound.height());
}
