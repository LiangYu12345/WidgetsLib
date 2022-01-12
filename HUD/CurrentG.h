#ifndef CURRENTG_H
#define CURRENTG_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT CurrentG : public QGraphicsItem
{
public:
    CurrentG();

    /// 设置数值
    void setValue(float value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_value = 1.0;
    const float m_lineWidth = 20;
    const float m_textWidth = 40;
};
#endif // CURRENTG_H
