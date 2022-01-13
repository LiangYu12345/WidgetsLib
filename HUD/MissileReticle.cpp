#include "MissileReticle.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

MissileReticle::MissileReticle()
{

}

void MissileReticle::setValue(QString value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF MissileReticle::boundingRect() const
{
    return QRectF();
}

void MissileReticle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(QPen(Qt::green));
    painter->setFont(QFont("Microsoft Yahei", 16));

    QFontMetricsF metrics(painter->font());
    auto textBound = metrics.boundingRect(m_value);
    //painter->drawText(QRectF(0, 0, textBound.width(), textBound.height()), Qt::AlignCenter, m_value);
}
