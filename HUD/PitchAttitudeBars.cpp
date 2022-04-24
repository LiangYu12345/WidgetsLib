#include "PitchAttitudeBars.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

PitchAttitudeBars::PitchAttitudeBars()
{

}

void PitchAttitudeBars::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF PitchAttitudeBars::boundingRect() const
{
    return QRectF(-100,-m_pixPerDegree * 5,200,m_pixPerDegree * 5);
}

void PitchAttitudeBars::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    auto boundRect = boundingRect();
    auto w = boundRect.width();
    auto h = boundRect.height();

    QPen pen(Qt::green);
    pen.setWidth(2);
    painter->setFont(QFont("Microsoft Yahei", 16));
    QFontMetricsF metrics(painter->font());

    int temp = (int)m_value/5 *5;

    //上刻度  value + 5
    QString uptext = QString::number(temp + 5);
    auto uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h  + m_pixPerDegree * m_value,-w/2 ,-h + m_pixPerDegree * m_value);   //矩形占比
    painter->drawLine(-w/2, -h + m_pixPerDegree * m_value,-w/2 ,-h+20 + m_pixPerDegree * m_value);
    painter->drawText(QRectF(-w, -h + m_pixPerDegree * m_value, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h + m_pixPerDegree * m_value,w/2 ,-h + m_pixPerDegree * m_value);
    painter->drawLine(w/2, -h + m_pixPerDegree * m_value,w/2 ,-h +20 + m_pixPerDegree * m_value);
    painter->drawText(QRectF(w-uptextBound.width(), -h + m_pixPerDegree * m_value, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);


    //下刻度 value - 5
    QString nexttext = QString::number(temp - 5);
    auto nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    QVector<qreal> dashes;
    dashes << 10 << 10 << 10 << 10;
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h + m_pixPerDegree * m_value,-w/2 ,h + m_pixPerDegree * m_value);    //矩形占比
    painter->drawLine(-w/2, h + m_pixPerDegree * m_value,-w/2 ,h -20 + m_pixPerDegree * m_value);
    painter->drawText(QRectF(-w, h - nexttextBound.height() + m_pixPerDegree * m_value, nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h + m_pixPerDegree * m_value,w/2 ,h + m_pixPerDegree * m_value);
    painter->drawLine(w/2, h + m_pixPerDegree * m_value,w/2 ,h -20 + m_pixPerDegree * m_value);
    painter->drawText(QRectF(w-nexttextBound.width(), h - nexttextBound.height() + m_pixPerDegree * m_value, nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

}
