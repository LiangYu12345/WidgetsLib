#include "huditem.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTimer>

void drawCorner(QPainter *painter, double width, double height, double ratio){
    auto width_2 = width/2;
    auto height_2 = height/2;
    auto w = width * ratio;
    auto h = height * ratio;
    QLineF lines[8];
    lines[0].setLine(-width_2, -height_2, -width_2+w, -height_2);
    lines[1].setLine(-width_2, -height_2, -width_2, -height_2+h);
    lines[2].setLine(width_2, -height_2, width_2-w, -height_2);
    lines[3].setLine(width_2, -height_2, width_2, -height_2+h);
    lines[4].setLine(width_2, height_2, width_2-w, height_2);
    lines[5].setLine(width_2, height_2, width_2, height_2-h);
    lines[6].setLine(-width_2, height_2, -width_2+w, height_2);
    lines[7].setLine(-width_2, height_2, -width_2, height_2-h);
    painter->drawLines(lines, 8);
};

Crosshair::Crosshair()
{
}

void Crosshair::setLMC(bool ready)
{
    if(m_lmc == ready)
        return;
    m_lmc = ready;
    update();
}

void Crosshair::setText(const QString &text)
{
    if(m_text == text)
        return;
    m_text = text;
    update();
}

QRectF Crosshair::boundingRect() const
{
    auto len_2 = m_len / 2;
    return {-len_2, -len_2, m_len+10, m_len};
}

void Crosshair::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    const auto holeLen = m_len / 5;
    const auto holeLen_2 = holeLen / 2;
    auto len_2 = m_len / 2 - 3;
    painter->setPen(Qt::white);
    QPointF crosshair[8] = {
        {-len_2, 0},
        {-holeLen_2, 0},
        {len_2, 0},
        {holeLen_2, 0},
        {0, -len_2},
        {0, -holeLen_2},
        {0, len_2},
        {0, holeLen_2},
    };
    painter->drawLines(crosshair, 4);
    //
    if(m_lmc) {
        const auto lineLen = holeLen / 2;
        const auto lineLen_2 = lineLen / 2;
        len_2 += 3;
        QPointF lmcSymbal[8] = {
            {-len_2, -lineLen_2},
            {-len_2, lineLen_2},
            {len_2, -lineLen_2},
            {len_2, lineLen_2},
            {-lineLen_2, -len_2},
            {lineLen_2, -len_2},
            {-lineLen_2, len_2},
            {lineLen_2, len_2}
        };
        painter->drawLines(lmcSymbal, 4);
    }
    //
    QFont font("Microsoft Yahei", 12);
    QFontMetricsF metrics(font);
    auto textRect = metrics.boundingRect(m_text);
    painter->setFont(font);
    painter->drawText(QRectF(len_2-textRect.width()/2, textRect.height()/5, textRect.width(), textRect.height()),
                      Qt::AlignCenter, m_text);
}

YawIndicator::YawIndicator()
{

}

void YawIndicator::setRange(float range)
{
    if(m_range == range)
        return;
    m_range = qBound(5.0f, range, 20.0f);
    update();
}

void YawIndicator::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF YawIndicator::boundingRect() const
{
    const float w = m_pixPerDegree * m_range;
    const float h = m_lineHeight + m_textHeight;
    return {-w/2, -m_textHeight, w, h};
}

void YawIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(Qt::green);
    painter->setPen(QPen(Qt::green, 3));
    painter->setFont(QFont("Microsoft Yahei", 12));
    painter->setClipRect(boundingRect());
    painter->translate(-m_value * m_pixPerDegree, 0);
    int start = m_value - m_range / 2;
    int end = m_value + m_range / 2;
    for(int i = start; i <= end; ++i) {
        int value = i;
        if(value < 0)
            value += 360;
        else if(value > 360)
            value -= 360;
        auto x = i * m_pixPerDegree;
        if(value % 5 == 0) {
            QFontMetricsF metrics(painter->font());
            QString text = QString::number(value);
            auto textBound = metrics.boundingRect(text);
            painter->drawLine(x, 0, x, m_lineHeight);
            painter->drawText(QRectF({x - textBound.width()/2, -m_textHeight}, textBound.size()), Qt::AlignHCenter|Qt::AlignTop, text);
        }
        else
            painter->drawLine(x, m_lineHeight/2, x, m_lineHeight);
    }
}


SpeedIndicator::SpeedIndicator()
{

}

void SpeedIndicator::setRange(float range)
{
    if(m_range == range)
        return;
    m_range = qBound(100.0f, range, 500.0f);
    update();
}

void SpeedIndicator::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF SpeedIndicator::boundingRect() const
{
    const float w = m_lineWidth + m_textWidth;
    const float h = m_pixPerDegree * m_range;
    return {-m_textWidth, -h/2, w, h};
}

void SpeedIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(Qt::green);
    painter->setPen(QPen(Qt::green, 3));
    painter->setFont(QFont("Microsoft Yahei", 12));
    painter->setClipRect(boundingRect());
    float start = m_value - m_range / 2;
    float end = m_value + m_range / 2;
    // clamp start to 10 times like as 10 20 30 etc
    start = int(start / 10) * 10 - 10;
    for(int i = start; i <= end; i+=10) {
        auto y = (m_value-i) * m_pixPerDegree;
        if(i % 50 == 0) {
            QFontMetricsF metrics(painter->font());
            QString text = QString::number(i);
            auto textBound = metrics.boundingRect(text);
            painter->drawLine(0, y, m_lineWidth, y);
            painter->drawText(QRectF(-m_textWidth, y-textBound.height()/2, m_textWidth, textBound.height()), Qt::AlignCenter, text);
        }
        else
            painter->drawLine(m_lineWidth/2, y, m_lineWidth, y);
    }
}

AltitudeIndicator::AltitudeIndicator()
{

}

void AltitudeIndicator::setRange(float range)
{
    if(m_range == range)
        return;
    m_range = qBound(100.0f, range, 500.0f);
    update();
}

void AltitudeIndicator::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

QRectF AltitudeIndicator::boundingRect() const
{
    const float w = m_lineWidth + m_textWidth;
    const float h = m_pixPerDegree * m_range;
    return {-m_lineWidth, -h/2, w, h};
}

void AltitudeIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(Qt::green);
    painter->setPen(QPen(Qt::green, 3));
    painter->setFont(QFont("Microsoft Yahei", 12));
    painter->setClipRect(boundingRect());
    float start = m_value - m_range / 2;
    float end = m_value + m_range / 2;
    // clamp start to 20 times like as 20 40 60 etc
    start = int(start / 20) * 20 - 20;
    for(int i = start; i <= end; i+=20) {
        auto y = (m_value-i) * m_pixPerDegree;
        if(i % 100 == 0) {
            QFontMetricsF metrics(painter->font());
            QString text = QString::number(i);
            auto textBound = metrics.boundingRect(text);
            painter->drawLine(-m_lineWidth, y, 0, y);
            painter->drawText(QRectF(0, y -textBound.height()/2, m_textWidth, textBound.height()), Qt::AlignCenter, text);
        }
        else
            painter->drawLine(-m_lineWidth, y, -m_lineWidth/2, y);
    }
}
RollIndicator::RollIndicator()
{

}

void RollIndicator::setRange(float range)
{
    if(m_range == range)
        return;
    m_range = qBound(100.0f, range, 500.0f);
    update();
}

void RollIndicator::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

void RollIndicator::setRadius(float radius)
{
    if(m_radius == radius)
        return;
    m_radius = radius;
    update();
}

const float &RollIndicator::radius() const
{
    return m_radius;
}

QRectF RollIndicator::boundingRect() const
{
    return {-m_radius, 0, m_radius * 2, m_radius*1.1};
}

void RollIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(Qt::green);
    painter->setPen(QPen(Qt::green, 2));
    painter->setClipRect(boundingRect());
    float start = m_value - m_range/2;
    float end = m_value + m_range/2;
    start = int(start / 5) * 5;
    painter->save();
    painter->rotate(start - m_value);
    for(int i = start; i <= end; i+=5) {
        if(i % 10 == 0)
            painter->drawLine(0, m_radius, 0, m_radius - m_lineLen);
        else
            painter->drawLine(0, m_radius-m_lineLen/2, 0, m_radius - m_lineLen);
        painter->rotate(5);
    }
    painter->restore();
    const float xDelta = m_lineLen / 4;
    const float yLen = m_lineLen / 2;
    QPointF triangle[3] = {
        QPointF(0, m_radius),
        QPointF(-xDelta, m_radius+yLen),
        QPointF(xDelta, m_radius+yLen)
    };
    painter->drawPolygon(triangle, 3);

}

LabelIndicator::LabelIndicator()
{

}

void LabelIndicator::setSize(const QSizeF &size)
{
    if(m_size == size)
        return;
    m_size = size;
    update();

}

void LabelIndicator::setText(const QString &text)
{
    if(m_text == text)
        return;
    m_text = text;
    update();
}

void LabelIndicator::setArrowAlignment(Qt::Alignment align)
{
    if(m_arrowAlign == align)
        return;
    m_arrowAlign = align;
    update();
}

void LabelIndicator::setArrowVisible(bool on)
{
    if(m_arrowVisible == on)
        return;
    m_arrowVisible = on;
    update();
}

void LabelIndicator::setBorder(const QPen &pen)
{
    if(m_borderPen == pen)
        return;
    m_borderPen = pen;
    update();
}

void LabelIndicator::setBrush(const QBrush &brush)
{
    if(m_brush == brush)
        return;
    m_brush = brush;
    update();
}

void LabelIndicator::setFont(const QFont &font)
{
    if(m_font == font)
        return;
    m_font = font;
    update();
}

void LabelIndicator::setPen(const QPen &pen)
{
    if(m_textPen == pen)
        return;
    m_textPen = pen;
    update();
}

QRectF LabelIndicator::boundingRect() const
{
    return {{-m_size.width()/2, -m_size.height()/2}, m_size};
}

void LabelIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(m_borderPen);
    painter->setBrush(m_brush);
    painter->setFont(m_font);
    const auto rect = boundingRect();
    if(m_arrowVisible) {
        QPointF polygon[5];
        if(m_arrowAlign == Qt::AlignBottom) {
            auto xDelta = rect.width()/2;
            auto yDelta = rect.height()/2;
            polygon[0] = {-xDelta, -yDelta};
            polygon[1] = {xDelta, -yDelta};
            polygon[2] = {xDelta, yDelta};
            polygon[3] = {0, yDelta*1.8};
            polygon[4] = {-xDelta, yDelta};
        }
        painter->drawPolygon(polygon, 5);
        painter->setPen(m_textPen);
        painter->drawText(rect, Qt::AlignCenter, m_text);
    }
    else {
        painter->drawRect(rect);
        painter->setPen(m_textPen);
        painter->drawText(rect, Qt::AlignCenter, m_text);
    }

}

FOVIndicator::FOVIndicator()
{

}

void FOVIndicator::setLevel(int level)
{
    if(level !=1 && level != 3 && level != 4 && m_level == level)
        return;
    m_level = level;
    update();
}

void FOVIndicator::setFov(float degree)
{
    if(m_fov == degree)
        return;
    m_fov = degree;
    auto fovLevel = m_fovLevel;
    if(m_fov > 1 && m_fov <= 5)
        fovLevel = 1;
    else if(m_fov > 5 && m_fov <= 10)
        fovLevel = 2;
    else if(m_fov > 10 && m_fov <= 30)
        fovLevel = 3;
    else if(m_fov > 30)
        fovLevel = 4;
    if(fovLevel == m_fovLevel)
        return;
    m_fovLevel = fovLevel;
    update();
}

void FOVIndicator::setSize(const QSizeF &size)
{
    if(m_size == size)
        return;
    m_size = size;
    update();
}

QRectF FOVIndicator::boundingRect() const
{
    return {{-m_size.width()/2, -m_size.height()/2}, m_size};
}

void FOVIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    const auto rect = boundingRect();
    painter->setPen(Qt::white);
    //
    auto deltaW = rect.width()/4;
    auto deltaH = rect.height()/4;
    auto deltaW_2 = deltaW/2;
    auto deltaH_2 = deltaH/2;
    // We will process level 1 later
    if(m_level == 3) {
        drawCorner(painter, deltaW*2, deltaH*2, 0.1);
        drawCorner(painter, deltaW*3, deltaH*3, 0.1);
        drawCorner(painter, deltaW*4, deltaH*4, 0.1);
    }
    else if(m_level == 4) {
        drawCorner(painter, deltaW*1, deltaH*1, 0.1);
        drawCorner(painter, deltaW*2, deltaH*2, 0.1);
        drawCorner(painter, deltaW*3, deltaH*3, 0.1);
        drawCorner(painter, deltaW*4, deltaH*4, 0.1);
    }
    if(m_level == 1)
        painter->drawRect(rect);
    else {
        switch (m_fovLevel) {
        case 1:
            painter->drawRect(-deltaW_2, -deltaH_2, deltaW, deltaH);
            break;
        case 2:
            painter->drawRect(-deltaW_2*2, -deltaH_2*2, deltaW*2, deltaH*2);
            break;
        case 3:
            painter->drawRect(-deltaW_2*3, -deltaH_2*3, deltaW*3, deltaH*3);
            break;
        case 4:
            painter->drawRect(-deltaW_2*4, -deltaH_2*4, deltaW*4, deltaH*4);
            break;
        }
    }
}

ProgressIndicator::ProgressIndicator()
{

}

void ProgressIndicator::setRange(float min, float max)
{
    if(m_min == min && m_max == max)
        return;
    m_min = min;
    m_max = max;
    update();
}

void ProgressIndicator::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

void ProgressIndicator::setSize(const QSizeF &size)
{
    if(m_size == size)
        return;
    m_size = size;
    update();
}

QRectF ProgressIndicator::boundingRect() const
{
    return {{-m_size.width()/2, -m_size.height()/2}, m_size};
}

/// 绘制代码时统一当作水平绘制，对于垂直绘制，只需要将画笔旋转90度即可
void ProgressIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    auto rect = boundingRect();
    bool hor = rect.width() > rect.height();
    auto width_2 = hor ? rect.width()/2 : rect.height()/2;
    auto height_2 = hor ? rect.height()/2 : rect.width()/2;
    auto spacing = hor ? rect.width() * 0.05 : rect.height() * 0.05;
    auto symbolWidth = hor ? rect.height() : rect.width();
    auto sliderWidth = hor ? rect.width() - symbolWidth * 2 - spacing * 2 : rect.height() - symbolWidth * 2 - spacing * 2;

    if(!hor)
        painter->rotate(-90);
    // 减号特殊一点，需要分类绘制
    painter->setPen(Qt::white);
    if(hor)
        painter->drawLine(-width_2, 0, -width_2+symbolWidth, 0);
    else {
        auto symbolWidth_2 = symbolWidth / 2;
        auto x = -width_2+symbolWidth_2;
        painter->drawLine(x, -symbolWidth_2, x, symbolWidth_2);
    }
    painter->drawLine(width_2, 0, width_2-symbolWidth, 0);
    painter->drawLine(width_2-symbolWidth/2, -symbolWidth/2, width_2-symbolWidth/2, symbolWidth/2);
    //
    QRectF sliderRect(-sliderWidth/2, -height_2, sliderWidth, height_2 * 2);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(255, 255, 255, 100));
    painter->drawRect(sliderRect);
    //
    auto rate = (m_value - m_min) / (m_max - m_min);
    sliderRect.setWidth(sliderRect.width() * rate);
    painter->setBrush(Qt::white);
    painter->drawRect(sliderRect);
}

AZIndicator::AZIndicator()
{

}

void AZIndicator::setValue(float degree)
{
    if(m_value == degree)
        return;
    m_value = degree;
    update();
}

void AZIndicator::setRadius(float radius)
{
    if(m_radius == radius)
        return;
    m_radius = radius;
    update();
}

QRectF AZIndicator::boundingRect() const
{
    return {-m_radius, -m_radius, m_radius*2, m_radius*2};
}

void AZIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    const auto lineLen = m_radius * 0.15;
    auto circleRadius = m_radius - lineLen;
    //
    painter->setPen(QPen(Qt::white, 2));
    painter->save();
    for(int i = 0; i <= 360; i+=45) {
        painter->drawLine(0, m_radius, 0, m_radius-lineLen);
        painter->rotate(45);
    }
    painter->restore();
    painter->drawEllipse({0, 0}, circleRadius, circleRadius);
    //
    const auto triangleHlen = lineLen*1.5;
    const auto triangleVLen = triangleHlen * 1.5;
    circleRadius -= 3;
    painter->rotate(m_value);
    painter->drawLine(0, 0, 0, -circleRadius+2);
    painter->setPen(Qt::white); // 1 pix width
    painter->setBrush(Qt::white);
    QPointF triangle[3] = {
        QPointF(-triangleHlen/2, triangleVLen-circleRadius),
        QPointF(triangleHlen/2, triangleVLen-circleRadius),
        QPointF(0, -circleRadius)
    };
    painter->drawPolygon(triangle, 3);
}

ELIndicator::ELIndicator()
{

}

void ELIndicator::setRange(float min, float max)
{
    if(m_min == min && m_max == max)
        return;
    m_min = min;
    m_max = max;
    update();
}

void ELIndicator::setValue(float value)
{
    if(m_value == value)
        return;
    m_value = value;
    update();
}

void ELIndicator::setSize(const QSizeF &size)
{
    if(m_size == size)
        return;
    m_size = size;
    update();
}


QRectF ELIndicator::boundingRect() const
{
    return {{-m_size.width() * (1-m_hRectRatio), -m_size.height()/2}, m_size};
}

void ELIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    const auto boundRect = boundingRect();
    const auto height_2 = boundRect.height() / 2;
    const auto hLineLen = boundRect.width() * m_hLineRatio;
    const auto hSpaceLen = boundRect.width() * m_hSpaceRatio;
    const auto hRectLen = boundRect.width() * m_hRectRatio;
    //
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    QPointF hLines[6] = {
        {-hLineLen/2-hSpaceLen, -height_2/2},
        {-hSpaceLen, -height_2/2},
        {-hLineLen-hSpaceLen, 0},
        {-hSpaceLen, 0},
        {-hLineLen/2-hSpaceLen, height_2/2},
        {-hSpaceLen, height_2/2}
    };
    painter->drawLines(hLines, 3);
    //
    QRectF sliderRect(0, -height_2, hRectLen, boundRect.height());
    painter->setPen(Qt::gray);
    painter->setBrush(QColor(255, 255, 255, 100));
    painter->drawRect(sliderRect);
    //
    auto rate = (m_value - m_min) / (m_max - m_min);
    sliderRect.setHeight(sliderRect.height() * rate);
    painter->setBrush(Qt::white);
    painter->drawRect(sliderRect);
}

NorthIndicator::NorthIndicator()
{
    doTransform();
}

void NorthIndicator::setValue(float degree)
{
    if(m_value == degree)
        return;
    m_value = degree;
    doTransform();
}

void NorthIndicator::setRadius(float radius)
{
    if(m_radius == radius)
        return;
    m_radius = radius;
    doTransform();
}

QRectF NorthIndicator::boundingRect() const
{
    return {-5, -7, 10, 14};
}

void NorthIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    const auto rect = boundingRect();
    const auto height_2 = rect.height()/2;
    const auto width_2 = rect.width()/2;
    QPointF triangle[3] = {
        {-width_2, height_2},
        {width_2, height_2},
        {0, -height_2}
    };
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawPolygon(triangle, 3);
}

void NorthIndicator::doTransform()
{
    QTransform transform;
    transform.rotate(m_value);
    transform.translate(0, -m_radius);
    this->setTransform(transform);
}

TrackIndicator::TrackIndicator()
{

}

void TrackIndicator::setSize(const QSizeF &size)
{
    if(m_size == size)
        return;
    m_size = size;
    update();
}

QRectF TrackIndicator::boundingRect() const
{
    return {-m_size.width()/2, -m_size.height()/2, m_size.width(), m_size.height()};
}

void TrackIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    auto rect = boundingRect();
    drawCorner(painter, rect.width(), rect.height(), 0.2);
}

SwitchIndicator::SwitchIndicator()
{

}

void SwitchIndicator::setSize(const QSizeF &size)
{
    if(m_size == size)
        return;
    m_size = size;
    update();
}

void SwitchIndicator::triggerRect()
{
    const int count = 5;
    const int msec = 250;
    for(int i = 0 ; i < count; ++i) {
        QTimer::singleShot(2 * i * msec, this, [&](){ m_showRect = true; update();});
        QTimer::singleShot(2 * i * msec + msec, this, [&](){ m_showRect = false; update();});
    }
}

void SwitchIndicator::triggerRetrack()
{
    m_showRetrack = true;
    update();
    QTimer::singleShot(1000, this, [&](){ m_showRetrack = false; update();});
}

QRectF SwitchIndicator::boundingRect() const
{
    return {-m_size.width()/2, -m_size.height()/2, m_size.width(), m_size.height()};
}

void SwitchIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    const auto rect = boundingRect();
    auto width_2 = rect.width()/2;
    auto height_2 = rect.height()/2;
    painter->setPen(Qt::green);
    QPointF crosshair[4] = {
        {-width_2, 0},
        {width_2, 0},
        {0, height_2},
        {0, -height_2}
    };
    painter->drawLines(crosshair, 2);
    //
    if(m_showRect) {
        drawCorner(painter, rect.width() * 0.8, rect.height() * 0.8, 0.4);
    }
    if(m_showRetrack) {
        painter->setPen({Qt::white, 2});
        painter->setBrush(Qt::white);
        width_2 *= 1.1;
        height_2 *= 1.1;
        QPointF crosshair[4] = {
            {-width_2, 0},
            {width_2, 0},
            {0, height_2},
            {0, -height_2}
        };
        painter->drawLines(crosshair, 2);
        drawCorner(painter, rect.width() * 0.5, rect.height() * 0.5, 0.05);
    }
}

PreTrackIndicator::PreTrackIndicator()
{

}

void PreTrackIndicator::setSize(const QSizeF &size)
{
    if(m_size == size)
        return;
    m_size = size;
    update();
}

QRectF PreTrackIndicator::boundingRect() const
{
    return {-m_size.width()/2, -m_size.height()/2, m_size.width(), m_size.height()};
}

void PreTrackIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    const auto rect = boundingRect();
    const auto width_2 = rect.width()/2;
    const auto height_2 = rect.height()/2;
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawLine(-width_2, -height_2, width_2, height_2);
    painter->drawLine(-width_2, height_2, width_2, -height_2);
}

LaserIndicator::LaserIndicator()
{
    connect(&m_timer, &QTimer::timeout, this, [&](){
        this->setVisible(!this->isVisible());
    });
    m_timer.setInterval(200);
}

void LaserIndicator::setLen(float len)
{
    if(m_len == len)
        return;
    m_len = len;
}

void LaserIndicator::trigger(int timeoutSecond)
{
    m_timer.start();
    if(timeoutSecond != 0)
        QTimer::singleShot(timeoutSecond * 1e3, this, &LaserIndicator::stop);
}

void LaserIndicator::stop()
{
    m_timer.stop();
    this->hide();
}

QRectF LaserIndicator::boundingRect() const
{
    return {-m_len/2, -m_len/2, m_len, m_len};
}

void LaserIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    const auto len_2 = m_len/2;
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    for(int i = 1; i <= 4; ++i) {
        painter->drawLine(0, -len_2, 0, len_2);
        painter->rotate(45);
    }
}
