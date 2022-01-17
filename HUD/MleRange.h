#ifndef MLERANGE_H
#define MLERANGE_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT MleRange : public QGraphicsItem
{
public:
    MleRange();
    void setValue(double value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    double m_value = 10;
    const float m_textWidth = 40;
};
#endif // MLERANGE_H
