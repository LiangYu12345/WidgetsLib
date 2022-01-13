#ifndef AIRSPEEDSCALESITEM_H
#define AIRSPEEDSCALESITEM_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT AirSpeedScalesItem : public QGraphicsItem
{
public:
    AirSpeedScalesItem();
    /// 设置跨度
    void setRange(float range);
    /// 设置中心数值
    void setValue(float value);

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_range = 160;
    float m_value = 0;
    const float m_pixPerDegree = 2;
    const float m_lineWidth = 20;
    const float m_textWidth = 40;
};
#endif // AIRSPEEDSCALESITEM_H
