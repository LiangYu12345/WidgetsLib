#ifndef FLIGHTPATHMARKER_H
#define FLIGHTPATHMARKER_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT FlightPathMarker : public QGraphicsItem
{
public:
    FlightPathMarker();
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    const float m_lineWidth = 20;
    const float m_textWidth = 40;
};
#endif // FLIGHTPATHMARKER_H
