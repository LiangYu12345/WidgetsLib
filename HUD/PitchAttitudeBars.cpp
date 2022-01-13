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
    return QRectF(-100,-400,200,800);
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
    QString text = QString::number(m_value);
    auto textBound = metrics.boundingRect(text);

    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h*4/10,-w/2 ,-h*4/10);   //矩形占比
    painter->drawLine(-w/2, -h*4/10,-w/2 ,-h*4/10+20);
    painter->drawText(QRectF(-w, -h*4/10, textBound.width(), textBound.height()), Qt::AlignCenter, QString::number(m_value));
    painter->drawLine(w, -h*4/10,w/2 ,-h*4/10);
    painter->drawLine(w/2, -h*4/10,w/2 ,-h*4/10+20);
    painter->drawText(QRectF(w-textBound.width(), -h*4/10, textBound.width(), textBound.height()), Qt::AlignCenter, QString::number(m_value));


    pen.setStyle(Qt::CustomDashLine);
    QVector<qreal> dashes;
    dashes << 10 << 10 << 10 << 10;
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h*4/10,-w/2 ,h*4/10);    //矩形占比
    painter->drawLine(-w/2, h*4/10,-w/2 ,h*4/10 -20);
    painter->drawText(QRectF(-w, h*4/10 - textBound.height(), textBound.width(), textBound.height()), Qt::AlignCenter, QString::number(m_value));
    painter->drawLine(w, h*4/10,w/2 ,h*4/10);
    painter->drawLine(w/2, h*4/10,w/2 ,h*4/10 -20);
    painter->drawText(QRectF(w, h*4/10 - textBound.height(), textBound.width(), textBound.height()), Qt::AlignCenter, QString::number(m_value));

}
