#ifndef BANKANGLEINDICATOR_H
#define BANKANGLEINDICATOR_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT  BankAngleIndicator : public QGraphicsItem
{
public:
    BankAngleIndicator();
    /// 设置跨度
     void setRange(float range);
     /// 设置数值
     void setValue(float value);
     /// 设置圆环半径
     void setRadius(float radius);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_range = 120;
    float m_value = 0;
    float m_radius = 100;
    const float m_lineLen = 15;
};
#endif // BANKANGLEINDICATOR_H
