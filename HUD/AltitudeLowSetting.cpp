#include "AltitudeLowSetting.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

AltitudeLowSetting::AltitudeLowSetting()
{

}

void AltitudeLowSetting::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF AltitudeLowSetting::boundingRect() const
{
    return QRectF();
}

void AltitudeLowSetting::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->setPen(QPen(Qt::green));
    painter->setFont(QFont("Microsoft Yahei", 16));

    QFontMetricsF metrics(painter->font());
    auto textBound = metrics.boundingRect(u8"AL  ");
    painter->drawText(QRectF(0,0,textBound.width(),textBound.height()),Qt::AlignLeft,QString(u8"AL"));

    auto valuetextBound = metrics.boundingRect(QString::number(m_value));
    painter->drawText(QRectF(textBound.width() + 10, 0, valuetextBound.width(), valuetextBound.height()), Qt::AlignCenter, QString::number(m_value));
}
