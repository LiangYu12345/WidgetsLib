#ifndef GREATCIRCLESTEERINGCUE_H
#define GREATCIRCLESTEERINGCUE_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT GreatCircleSteeringCue : public QGraphicsItem
{
public:
    GreatCircleSteeringCue();
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    const float m_lineWidth = 20;
};
#endif // GREATCIRCLESTEERINGCUE_H
