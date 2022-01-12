#ifndef ROLLINDICATOR_H
#define ROLLINDICATOR_H

#include "../widgetslib_global.h"

#include <QGraphicsItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT f16RollIndicator : public QGraphicsItem
{
public:
    f16RollIndicator();
    /// 设置跨度
    void setRange(float range);
    /// 设置中心数值
    void setValue(float value);
    /// 设置圆环半径
    void setRadius(float radius);
    const float &radius() const;

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_range = 80;
    float m_value = 0;
    float m_radius = 400;
    const float m_lineLen = 20;
    const float m_textWidth = 40;
};
#endif // ROLLINDICATOR_H
