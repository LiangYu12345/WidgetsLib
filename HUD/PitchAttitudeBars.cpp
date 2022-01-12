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
    return QRectF();
}

void PitchAttitudeBars::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    auto boundRect = boundingRect();
    auto w = boundRect.width();
    auto h = boundRect.height();

    QPen pen;
    QFontMetricsF metrics(painter->font());
    QString text = QString::number(m_value);
    auto textBound = metrics.boundingRect(text);
    if(m_value > 0)
    {
        pen.setStyle(Qt::SolidLine);
        painter->setPen(pen);
        painter->drawLine(-w, h,-w/2 ,h);   //矩形占比
        painter->drawLine(-w/2, h,-w/2 ,h+5);
        painter->drawText(QRectF(0, 0, textBound.width(), textBound.height()), Qt::AlignCenter, QString::number(m_value));
        painter->drawLine(w, h,w/2 ,h);
        painter->drawLine(w/2, h,w/2 ,h+5);
        painter->drawText(QRectF(0, 0, textBound.width(), textBound.height()), Qt::AlignCenter, QString::number(m_value));
    }
    else
    {
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->drawLine(-w, h,-w/2 ,h);    //矩形占比
        painter->drawLine(-w/2, h,-w/2 ,h-5);
        painter->drawText(QRectF(0, 0, textBound.width(), textBound.height()), Qt::AlignCenter, QString::number(m_value));
        painter->drawLine(w, h,w/2 ,h);
        painter->drawLine(w/2, h,w/2 ,h-5);
        painter->drawText(QRectF(0, 0, textBound.width(), textBound.height()), Qt::AlignCenter, QString::number(m_value));
    }


}
