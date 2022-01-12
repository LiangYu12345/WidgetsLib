#ifndef STEERPOINT_H
#define STEERPOINT_H

#include "widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class Steerpoint : public QGraphicsItem
{
public:
    Steerpoint();
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    const float m_lineWidth = 20;
};
#endif // STEERPOINT_H
