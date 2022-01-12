#ifndef MAXGS_H
#define MAXGS_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT MaxGs : public QGraphicsItem
{
public:
    MaxGs();
    /// 设置数值
    void setValue(float value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_value = 0;
    const float m_lineWidth = 20;
    const float m_textWidth = 40;
};
#endif // MAXGS_H
