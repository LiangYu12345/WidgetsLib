#ifndef HEADINGSCALE_H
#define HEADINGSCALE_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT HeadingScale : public QGraphicsItem
{
public:
    HeadingScale();
    /// 设置跨度
    void setRange(float range);
    /// 设置数值
    void setValue(float value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_range = 20;
    float m_value = 70;
    const float m_pixPerDegree = 8;
    const float m_lineHeight = 20;
    const float m_textHeight = 40;
};
#endif // HEADINGSCALE_H
