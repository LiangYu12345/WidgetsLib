#ifndef OFFSETAIMPOINT_H
#define OFFSETAIMPOINT_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT OffsetAimpoint : public QGraphicsItem
{
public:
    OffsetAimpoint();
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
};
#endif // OFFSETAIMPOINT_H
