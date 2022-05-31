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

void PitchAttitudeBars::setInclinationAngleValue(float value)
{
    if(m_angle == value)
        return;
    m_angle = value;
    update();
}

QRectF PitchAttitudeBars::boundingRect() const
{
    return QRectF(-960,-540,1920,1080); // -100 -320 200 320
}

void PitchAttitudeBars::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    auto boundRect = boundingRect();
    auto h = 320;
    auto w = 200;

    QPen pen(Qt::green);
    pen.setWidth(2);
    painter->setFont(QFont("Microsoft Yahei", 16));
    QFontMetricsF metrics(painter->font());

    // 画笔旋转
    painter->save();
    painter->rotate(m_angle);

    //  还需考虑翻转的情况
    painter->translate(0,m_value * m_pixPerDegree);

    // 90 - 0        //  5 刻度为 160  10 刻度为320 像素
    QString uptext = QString::number(90);
    auto uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 18,-w/2 ,-h * 18);   //矩形占比
    painter->drawLine(-w/2, -h * 18,-w/2 ,-h * 18+20);
    painter->drawText(QRectF(-w, -h * 18, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 18,w/2 ,-h * 18);
    painter->drawLine(w/2, -h * 18,w/2 ,-h * 18 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 18, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(85);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 17,-w/2 ,-h * 17);   //矩形占比
    painter->drawLine(-w/2, -h * 17,-w/2 ,-h * 17+20);
    painter->drawText(QRectF(-w, -h * 17, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 17,w/2 ,-h * 17);
    painter->drawLine(w/2, -h * 17,w/2 ,-h * 17 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 17, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(80);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 16,-w/2 ,-h * 16);   //矩形占比
    painter->drawLine(-w/2, -h * 16,-w/2 ,-h * 16+20);
    painter->drawText(QRectF(-w, -h * 16, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 16,w/2 ,-h * 16);
    painter->drawLine(w/2, -h * 16,w/2 ,-h * 16 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 16, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(75);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 15,-w/2 ,-h * 15);   //矩形占比
    painter->drawLine(-w/2, -h  * 15,-w/2 ,-h * 15+20);
    painter->drawText(QRectF(-w, -h * 15, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 15,w/2 ,-h * 15);
    painter->drawLine(w/2, -h * 15,w/2 ,-h * 15 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 15, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(70);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 14,-w/2 ,-h * 14);   //矩形占比
    painter->drawLine(-w/2, -h  * 14,-w/2 ,-h * 14+20);
    painter->drawText(QRectF(-w, -h * 14, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 14,w/2 ,-h * 14);
    painter->drawLine(w/2, -h * 14,w/2 ,-h * 14 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 14, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(65);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 13,-w/2 ,-h * 13);   //矩形占比
    painter->drawLine(-w/2, -h * 13,-w/2 ,-h * 13+20);
    painter->drawText(QRectF(-w, -h * 13, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 13,w/2 ,-h * 13);
    painter->drawLine(w/2, -h * 13,w/2 ,-h * 13 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 13, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(60);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 12,-w/2 ,-h * 12);   //矩形占比
    painter->drawLine(-w/2, -h * 12,-w/2 ,-h * 12+20);
    painter->drawText(QRectF(-w, -h * 12, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 12,w/2 ,-h * 12);
    painter->drawLine(w/2, -h * 12,w/2 ,-h * 12 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 12, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(55);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 11,-w/2 ,-h * 11);   //矩形占比
    painter->drawLine(-w/2, -h * 11,-w/2 ,-h * 11+20);
    painter->drawText(QRectF(-w, -h * 11, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 11,w/2 ,-h * 11);
    painter->drawLine(w/2, -h * 11,w/2 ,-h * 11 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 11, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(50);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 10,-w/2 ,-h * 10);   //矩形占比
    painter->drawLine(-w/2, -h * 10,-w/2 ,-h * 10+20);
    painter->drawText(QRectF(-w, -h * 10, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 10,w/2 ,-h * 10);
    painter->drawLine(w/2, -h * 10,w/2 ,-h * 10 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 10, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(45);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 9,-w/2 ,-h * 9);   //矩形占比
    painter->drawLine(-w/2, -h * 9,-w/2 ,-h * 9+20);
    painter->drawText(QRectF(-w, -h * 9, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 9,w/2 ,-h * 9);
    painter->drawLine(w/2, -h * 9,w/2 ,-h * 9 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 9, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(40);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 8,-w/2 ,-h * 8);   //矩形占比
    painter->drawLine(-w/2, -h * 8,-w/2 ,-h * 8+20);
    painter->drawText(QRectF(-w, -h * 8, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 8,w/2 ,-h * 8);
    painter->drawLine(w/2, -h * 8,w/2 ,-h * 8 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 8, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(35);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 7,-w/2 ,-h * 7);   //矩形占比
    painter->drawLine(-w/2, -h * 7,-w/2 ,-h * 7+20);
    painter->drawText(QRectF(-w, -h * 6, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 7,w/2 ,-h * 7);
    painter->drawLine(w/2, -h * 7,w/2 ,-h * 7 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 7, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(30);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 6,-w/2 ,-h * 6);   //矩形占比
    painter->drawLine(-w/2, -h * 6,-w/2 ,-h * 6+20);
    painter->drawText(QRectF(-w, -h * 6, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 6,w/2 ,-h * 6);
    painter->drawLine(w/2, -h * 6,w/2 ,-h * 6 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 6, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(25);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 5,-w/2 ,-h * 5);   //矩形占比
    painter->drawLine(-w/2, -h * 5,-w/2 ,-h * 5+20);
    painter->drawText(QRectF(-w, -h * 5, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 5,w/2 ,-h * 5);
    painter->drawLine(w/2, -h * 5,w/2 ,-h * 5 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 5, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(20);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 4,-w/2 ,-h * 4);   //矩形占比
    painter->drawLine(-w/2, -h * 4,-w/2 ,-h * 4+20);
    painter->drawText(QRectF(-w, -h * 4, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 4,w/2 ,-h * 4);
    painter->drawLine(w/2, -h * 4,w/2 ,-h * 4 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 4, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(15);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 3,-w/2 ,-h * 3);   //矩形占比
    painter->drawLine(-w/2, -h * 3,-w/2 ,-h * 3+20);
    painter->drawText(QRectF(-w, -h * 3, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 3,w/2 ,-h * 3);
    painter->drawLine(w/2, -h * 3,w/2 ,-h * 3 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 3, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(10);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h * 2,-w/2 ,-h * 2);   //矩形占比
    painter->drawLine(-w/2, -h * 2,-w/2 ,-h * 2 + 20);
    painter->drawText(QRectF(-w, -h * 2, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h * 2,w/2 ,-h * 2);
    painter->drawLine(w/2, -h * 2,w/2 ,-h * 2 +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h * 2, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    uptext = QString::number(5);
    uptextBound = metrics.boundingRect(uptext);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(-w, -h,-w/2 ,-h);   //矩形占比
    painter->drawLine(-w/2, -h ,-w/2 ,-h+20);
    painter->drawText(QRectF(-w, -h, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);
    painter->drawLine(w, -h ,w/2 ,-h);
    painter->drawLine(w/2, -h ,w/2 ,-h +20);
    painter->drawText(QRectF(w-uptextBound.width(), -h, uptextBound.width(), uptextBound.height()), Qt::AlignCenter, uptext);

    // 水平线
    painter->save();

    QPen hpen(Qt::gray);
    hpen.setWidth(2);
    painter->setPen(hpen);

    auto hw = boundRect.width();
    //auto hh = boundRect.height();
    painter->drawLine(-hw,0,-hw/20,0);
    painter->drawLine(hw,0,hw/20,0);

    painter->restore();

    //下刻度 value - 5
    // 0 - -90
    QString nexttext = QString::number(-5);

    auto nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    QVector<qreal> dashes;
    dashes << 10 << 10 << 10 << 10;
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h + 5,-w/2 ,h);    //矩形占比
    painter->drawLine(-w/2, h,-w/2 ,h -20);
    painter->drawText(QRectF(-w, h - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h + 5,w/2 ,h);
    painter->drawLine(w/2, h,w/2 ,h -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-10);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 2 + 10,-w/2 ,h * 2);    //矩形占比
    painter->drawLine(-w/2, h * 2,-w/2 ,h * 2 -20);
    painter->drawText(QRectF(-w, h * 2 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 2 + 10,w/2 ,h * 2);
    painter->drawLine(w/2, h * 2,w/2 ,h * 2 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 2 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-15);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 3 + 15,-w/2 ,h * 3);    //矩形占比
    painter->drawLine(-w/2, h * 3,-w/2 ,h * 3 -20);
    painter->drawText(QRectF(-w, h * 3 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 3 + 15,w/2 ,h * 3);
    painter->drawLine(w/2, h * 3,w/2 ,h * 3 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 3 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-20);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 4 + 20,-w/2 ,h * 4);    //矩形占比
    painter->drawLine(-w/2, h * 4,-w/2 ,h * 4 -20);
    painter->drawText(QRectF(-w, h * 4 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 4 + 20,w/2 ,h * 4);
    painter->drawLine(w/2, h * 4,w/2 ,h * 4 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 4 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-25);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 5 + 25,-w/2 ,h * 5);    //矩形占比
    painter->drawLine(-w/2, h * 5,-w/2 ,h * 5 -20);
    painter->drawText(QRectF(-w, h * 5 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 5 + 25,w/2 ,h * 5);
    painter->drawLine(w/2, h * 5,w/2 ,h * 5 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 5 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-30);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 6 + 30,-w/2 ,h * 6);    //矩形占比
    painter->drawLine(-w/2, h * 6,-w/2 ,h * 6 -20);
    painter->drawText(QRectF(-w, h * 6 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 6 + 30,w/2 ,h * 6);
    painter->drawLine(w/2, h * 6,w/2 ,h * 6 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 6 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-35);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 7 + 35,-w/2 ,h * 7);    //矩形占比
    painter->drawLine(-w/2, h * 7,-w/2 ,h * 7 -20);
    painter->drawText(QRectF(-w, h * 7 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 7 + 35,w/2 ,h * 7);
    painter->drawLine(w/2, h * 7,w/2 ,h * 7 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 7 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-40);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 8 + 40,-w/2 ,h * 8);    //矩形占比
    painter->drawLine(-w/2, h * 8,-w/2 ,h * 8 -20);
    painter->drawText(QRectF(-w, h * 8 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 8 + 40,w/2 ,h * 8);
    painter->drawLine(w/2, h * 8,w/2 ,h * 8 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 8 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-45);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 9 + 45,-w/2 ,h * 9);    //矩形占比
    painter->drawLine(-w/2, h * 9,-w/2 ,h * 9 -20);
    painter->drawText(QRectF(-w, h * 9 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 9 + 45,w/2 ,h * 9);
    painter->drawLine(w/2, h  * 9,w/2 ,h * 9 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 9 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-50);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 10 + 50,-w/2 ,h * 10);    //矩形占比
    painter->drawLine(-w/2, h * 10,-w/2 ,h * 10 -20);
    painter->drawText(QRectF(-w, h * 10 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 10 + 50,w/2 ,h * 10);
    painter->drawLine(w/2, h  * 10,w/2 ,h * 10 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 10 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-55);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 11 + 55,-w/2 ,h * 11);    //矩形占比
    painter->drawLine(-w/2, h * 11,-w/2 ,h * 11 -20);
    painter->drawText(QRectF(-w, h * 11 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 11 + 55,w/2 ,h * 11);
    painter->drawLine(w/2, h * 11,w/2 ,h * 11 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 11 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-60);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 12 + 60,-w/2 ,h * 12);    //矩形占比
    painter->drawLine(-w/2, h * 12,-w/2 ,h * 12 -20);
    painter->drawText(QRectF(-w, h * 12 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 12 + 60,w/2 ,h * 12);
    painter->drawLine(w/2, h * 12,w/2 ,h * 12 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 12 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-65);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 13 + 65,-w/2 ,h * 13);    //矩形占比
    painter->drawLine(-w/2, h * 13,-w/2 ,h * 13 -20);
    painter->drawText(QRectF(-w, h * 13 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 13 + 65,w/2 ,h * 13);
    painter->drawLine(w/2, h * 13,w/2 ,h * 13 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 13 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-70);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 14 + 70,-w/2 ,h * 14);    //矩形占比
    painter->drawLine(-w/2, h * 14,-w/2 ,h * 14 -20);
    painter->drawText(QRectF(-w, h * 14 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 14 + 70,w/2 ,h * 14);
    painter->drawLine(w/2, h * 14,w/2 ,h * 14 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 14 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-75);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 15 + 75,-w/2 ,h * 15);    //矩形占比
    painter->drawLine(-w/2, h * 15,-w/2 ,h * 15 -20);
    painter->drawText(QRectF(-w, h * 15 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 15 + 75,w/2 ,h * 15);
    painter->drawLine(w/2, h * 15,w/2 ,h * 15 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 15 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-80);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 16 + 80,-w/2 ,h * 16);    //矩形占比
    painter->drawLine(-w/2, h * 16,-w/2 ,h * 16 -20);
    painter->drawText(QRectF(-w, h * 16 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 16 + 80,w/2 ,h * 16);
    painter->drawLine(w/2, h * 16,w/2 ,h * 16 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 16 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-85);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 17 + 85,-w/2 ,h * 17);    //矩形占比
    painter->drawLine(-w/2, h * 17,-w/2 ,h * 17 -20);
    painter->drawText(QRectF(-w, h * 17 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 17 + 85,w/2 ,h * 17);
    painter->drawLine(w/2, h * 17,w/2 ,h * 17 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 17 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    nexttext = QString::number(-90);
    nexttextBound = metrics.boundingRect(nexttext);
    pen.setStyle(Qt::CustomDashLine);
    pen.setDashPattern(dashes);
    painter->setPen(pen);
    painter->drawLine(-w, h * 18 + 90,-w/2 ,h * 18);    //矩形占比
    painter->drawLine(-w/2, h * 18,-w/2 ,h * 18 -20);
    painter->drawText(QRectF(-w, h * 18 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);
    painter->drawLine(w, h * 18 + 90,w/2 ,h * 18);
    painter->drawLine(w/2, h * 18,w/2 ,h * 18 -20);
    painter->drawText(QRectF(w-nexttextBound.width(), h * 18 - nexttextBound.height(), nexttextBound.width(), nexttextBound.height()), Qt::AlignCenter, nexttext);

    painter->restore();
}
