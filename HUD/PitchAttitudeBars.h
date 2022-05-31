#ifndef PITCHATTITUDEBARS_H
#define PITCHATTITUDEBARS_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT PitchAttitudeBars : public QGraphicsItem
{
public:
    PitchAttitudeBars();
    /// 设置具体俯仰值
    void setValue(float value);
    /// 设置倾斜角度 (画笔倾斜角度)
    void setInclinationAngleValue(float value);
    /// 外部设置俯仰角的显示位置
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_value = 0;
    float m_angle = 0;
    const float m_lineWidth = 20;
    const float m_textWidth = 40;
    const float m_pixPerDegree = 64;
};
#endif // PITCHATTITUDEBARS_H
