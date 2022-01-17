#include "AAMissileType.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

AAMissileType::AAMissileType()
{

}

void AAMissileType::setValue(double value)
{
    if(m_valuefirst == value)
        return;
    m_valuefirst = value;
    update();
}

QRectF AAMissileType::boundingRect() const
{
    return QRectF();
}

void AAMissileType::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(QPen(Qt::green));
    painter->setFont(QFont("Microsoft Yahei", 16));

    QFontMetricsF metrics(painter->font());
    auto textBoundarm = metrics.boundingRect(m_armtext);
    painter->drawText(QRectF(0, 0, textBoundarm.width(), textBoundarm.height()), Qt::AlignCenter, m_armtext);
    auto textBoundfirst = metrics.boundingRect(QString::number(m_valuefirst));
    painter->drawText(QRectF(0, textBoundarm.height(), textBoundfirst.width(), textBoundfirst.height()), Qt::AlignCenter, QString::number(m_valuefirst));
    auto textBoundsecond = metrics.boundingRect(QString::number(m_valuesecond));
    painter->drawText(QRectF(-textBoundsecond.width(), textBoundfirst.height() + textBoundarm.height(), textBoundsecond.width(), textBoundsecond.height()), Qt::AlignCenter, QString::number(m_valuesecond));
    auto textBoundthird = metrics.boundingRect(QString::number(m_valuethird));
    painter->drawText(QRectF(-textBoundsecond.width(), textBoundsecond.height() + textBoundfirst.height() + textBoundarm.height(), textBoundthird.width(), textBoundthird.height()), Qt::AlignCenter, QString::number(m_valuethird));
   auto textBoundm_srm = metrics.boundingRect(m_srmtext);
    painter->drawText(QRectF(textBoundthird.width(), textBoundarm.height() + textBoundsecond.height() + textBoundfirst.height(), textBoundm_srm.width(), textBoundm_srm.height()), Qt::AlignCenter, m_srmtext);
}
