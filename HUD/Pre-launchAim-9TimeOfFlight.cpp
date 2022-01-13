#include "Pre-launchAim-9TimeOfFlight.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

PrelaunchAim9TimeOfFlight::PrelaunchAim9TimeOfFlight()
{

}

void PrelaunchAim9TimeOfFlight::setValue(QString value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF PrelaunchAim9TimeOfFlight::boundingRect() const
{
    return QRectF();
}

void PrelaunchAim9TimeOfFlight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(QPen(Qt::green));
    painter->setFont(QFont("Microsoft Yahei", 16));

    QFontMetricsF metrics(painter->font());
    auto textBound = metrics.boundingRect(m_value);
    //painter->drawText(QRectF(0, 0, textBound.width(), textBound.height()), Qt::AlignCenter, m_value);
}
