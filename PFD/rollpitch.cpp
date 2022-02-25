#include "rollpitch.h"
#include <QPainter>
#include <QtMath>

static double preciseRound(double src, int precision)
{
    double tmp = qPow(10,precision);
    return qRound64(src * tmp) / tmp;
}

RollPitch::RollPitch(QWidget *parent) : QWidget(parent)
  ,m_roll(0.f)
  ,m_pitch(0.f)
  ,m_isCheckable(true)
  ,m_isChecked(false)
  ,m_rollPrecision(1)
  ,m_pitchPrecision(1)
{
}

void RollPitch::setUavID(int id)
{
    m_id = id;
}

int RollPitch::ID()
{
    return  m_id;
}

void RollPitch::setRoll(float roll)
{
    roll = static_cast<float>(preciseRound(static_cast<double>(roll), m_rollPrecision));
    float value;
    if(roll < -180)
        value = -180;
    else if (roll > 180)
        value = 180;
    else
        value = roll;
//    if(m_roll != value)
    if(m_roll > value || m_roll < value)
    {
        m_roll = value;
        update();
    }
}

void RollPitch::setPitch(float pitch)
{
    pitch = static_cast<float>(preciseRound(static_cast<double>(pitch), m_pitchPrecision));
    float value;
    if(pitch < -90)
        value = -90;
    else if (pitch > 90)
        value = 90;
    else
        value = pitch;

//    if(m_pitch != value)
    if(m_pitch > value || m_pitch < value)
    {
        m_pitch = value;
        update();
    }
}

void RollPitch::doubleClick()
{
    if(m_isCheckable)
    {
        setChecked(true);
        emit this->checked();
    }
}

void RollPitch::setChecked(bool checked)
{
    if(m_isChecked == checked)
        return;
    m_isChecked = checked;
    update();
}

void RollPitch::setCheckable(bool able)
{
    m_isCheckable = able;
}

void RollPitch::setRollPrecision(int prec)
{
    m_rollPrecision = prec;
}

void RollPitch::setPitchPrecision(int prec)
{
    m_pitchPrecision = prec;
}

void RollPitch::setPrecision(int prec)
{
    m_rollPrecision = m_pitchPrecision = prec;
}

void RollPitch::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    const float marginFactory = 0.05f;
    const int windowSize = 100;
    const int windowSize_2 = windowSize/2;
    const int rollRadius = windowSize/2 * 2/3;
    const int rollWidth = 6;
    const int pitchWidth = 10;
    const float pitchHeight = rollRadius * 3 / 2;
    const float pitchJump = 30;    //the min and max visual differece value in graphics

    /* draw all graphics in logical system by @windowSize;
     * add there is a @marginFactory indicator the margin space */
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    int marginH = static_cast<int>(this->width() * marginFactory);
    int marginV = static_cast<int>(this->height() * marginFactory);
    QRect viewPort(marginH, marginV, this->width()-2*marginH, this->height()-2*marginV);
    painter.setViewport(viewPort);
    painter.setWindow(0, 0, windowSize, windowSize);

    //To Note: excpet that border style when clicked;
    //all the other components are drawing inside a ellipse
    /* 1.draw background by pitch and roll */
    painter.save();
    QPainterPath clipPath;
    clipPath.addEllipse(0,0,windowSize,windowSize);
    painter.setClipPath(clipPath);

    qreal rot = -static_cast<qreal>(m_roll);
    qreal trans = static_cast<qreal>(m_pitch * windowSize / 180.f);
    painter.translate(windowSize_2, windowSize_2);
    painter.rotate(rot);
    painter.translate(0, trans);

    QLinearGradient blue(0, -windowSize, 0, 0);
    blue.setColorAt(0, QColor::fromRgb(93, 173, 226));
    blue.setColorAt(1, QColor::fromRgb(40, 116, 166));
    painter.fillRect(-windowSize_2, -windowSize, windowSize, windowSize, blue);

    QLinearGradient green(0, 0, 0, windowSize);
    green.setColorAt(0, QColor::fromRgb(30, 132, 73));
    green.setColorAt(1, QColor::fromRgb(82, 190, 128));
    painter.fillRect(-windowSize_2, 0, windowSize, windowSize, green);
    painter.restore();

    /* 2.draw pitch indicator */
    painter.save();
    painter.setPen(Qt::white);
    QRectF pitchClip(0, static_cast<qreal>(windowSize-pitchHeight)/2,
                     windowSize,static_cast<qreal>(pitchHeight));
    painter.setClipRect(pitchClip);

    painter.translate(windowSize_2, windowSize_2);
    float pitchInterval = pitchHeight / pitchJump;    //the logic length of every horizatal line indicator
    painter.translate(0, -static_cast<qreal>(m_pitch * pitchInterval));
    int pitchMax = qCeil(static_cast<qreal>(m_pitch + pitchJump/2));
    int pitchMin = qFloor(static_cast<qreal>(m_pitch - pitchJump/2));
    QFont font(QString("Microsoft Yahei light"), pitchWidth/2);
    QFontMetricsF metrix(font);
    qreal fontHight = metrix.height();
    for(int i = pitchMin; i <= pitchMax; ++i)
    {
        if(i % 5 == 0)
        {
            QLineF line(static_cast<qreal>(-pitchWidth/2), static_cast<qreal>(pitchInterval*i),
                        static_cast<qreal>(pitchWidth/2), static_cast<qreal>(pitchInterval*i));
            painter.drawLine(line);

            painter.save();
            painter.setFont(font);
            painter.drawText(QRectF(pitchWidth, line.y2()-fontHight/2, static_cast<qreal>(pitchHeight), fontHight), Qt::AlignLeft, QString::number(i));
            painter.restore();
        }
        else
            painter.drawLine(QLineF(static_cast<qreal>(-pitchWidth/4), static_cast<qreal>(pitchInterval*i),
                                    static_cast<qreal>(pitchWidth/4), static_cast<qreal>(pitchInterval*i)));
    }
    painter.restore();

    painter.save();
    painter.translate(windowSize_2, windowSize_2);
    painter.setPen(Qt::red);
    painter.drawArc(-pitchWidth/2, -pitchWidth/2, pitchWidth, pitchWidth, 0, -180*16);
    painter.drawLine(-pitchWidth, 0, -pitchWidth/2, 0);
    painter.drawLine(pitchWidth, 0, pitchWidth/2, 0);
    painter.restore();

    /* 3.draw roll indicator */
    painter.save();
    painter.setPen(Qt::white);
    painter.translate(windowSize_2, windowSize_2);
    painter.drawArc(-rollRadius, -rollRadius, 2*rollRadius, 2*rollRadius, -60*16, 120*16);
    painter.drawArc(-rollRadius, -rollRadius, 2*rollRadius, 2*rollRadius, 120*16, 120*16);

    painter.save();
    painter.rotate(60);
    //indicator
    for(int i = 0; i <= 20; ++i)
    {
        if(i % 5 == 0)
            painter.drawLine(rollRadius, 0, rollRadius+rollWidth, 0);
        else
            painter.drawLine(rollRadius, 0, rollRadius+rollWidth/2, 0);
        painter.rotate(-120/20);
    }
    painter.restore();
    painter.save();
    painter.rotate(-120);
    for(int i = 0; i <= 20; ++i)
    {
        if(i % 5 == 0)
            painter.drawLine(rollRadius, 0, rollRadius+rollWidth, 0);
        else
            painter.drawLine(rollRadius, 0, rollRadius+rollWidth/2, 0);
        painter.rotate(-120/20);
    }
    painter.restore();
    //number
    painter.setFont(font);
    for(int i = -60; i <= 60; i+=30)
    {
        qreal x = (rollRadius+rollWidth)*qCos(qDegreesToRadians(static_cast<qreal>(-i)));
        qreal y = (rollRadius+rollWidth)*qSin(qDegreesToRadians(static_cast<qreal>(-i)));
        painter.drawText(QRectF(x, y-fontHight/2, 2*rollWidth, fontHight), Qt::AlignCenter, QString::number(i));
    }
    for(int i = -60; i <= 60; i+=30)
    {
        qreal x = (rollRadius+rollWidth)*qCos(qDegreesToRadians(static_cast<qreal>(i-180)));
        qreal y = (rollRadius+rollWidth)*qSin(qDegreesToRadians(static_cast<qreal>(i-180)));
        painter.drawText(QRectF(x-2*rollWidth, y-fontHight/2, 2*rollWidth, fontHight), Qt::AlignCenter, QString::number(i));
    }
    painter.restore();

    painter.save();
    painter.translate(windowSize_2, windowSize_2);
    painter.rotate(static_cast<qreal>(-m_roll));
    painter.setPen(Qt::red);
    painter.drawLine(-windowSize_2, 0, -rollRadius, 0);
    painter.drawLine(rollRadius, 0, windowSize_2, 0);
    painter.restore();

    /* draw pitch and roll text */
    painter.save();
    QString pitchText = QStringLiteral("俯仰:");
    QString rollText = QStringLiteral("横滚:");
    painter.setFont(font);
    painter.setPen(Qt::white);
    QRectF pitchBound = metrix.boundingRect(pitchText);
    painter.translate(windowSize_2-pitchBound.width(), 0);
    int hOff = (windowSize_2-static_cast<int>(pitchHeight/2)-static_cast<int>(pitchBound.height()))/2;

    QRectF pitchRect(0, hOff, static_cast<int>(pitchBound.width()), static_cast<int>(pitchBound.height()));
    painter.drawText(pitchRect, Qt::AlignCenter, pitchText);
    QRectF rollRect(0, windowSize - hOff - static_cast<int>(pitchBound.height()), static_cast<int>(pitchBound.width()), static_cast<int>(pitchBound.height()));
    painter.drawText(rollRect, Qt::AlignCenter, rollText);

    painter.drawText(pitchRect.translated(pitchRect.width(), 0), Qt::AlignCenter, QString::number(static_cast<qreal>(m_pitch)));
    painter.drawText(rollRect.translated(rollRect.width(), 0), Qt::AlignCenter, QString::number(static_cast<qreal>(m_roll)));

    painter.restore();

    //draw checked border
    if(!m_isChecked)
        return;
    painter.save();
    painter.setPen(QPen(QColor::fromRgb(93, 173, 226),2));
    qreal borderOff = static_cast<qreal>(windowSize*marginFactory/2);
    QRectF borderRect(-borderOff, -borderOff, windowSize+2*borderOff, windowSize+2*borderOff);
    painter.drawEllipse(borderRect);
    painter.restore();
}

void RollPitch::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    doubleClick();
}

