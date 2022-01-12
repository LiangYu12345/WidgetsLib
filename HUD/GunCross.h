#ifndef GUNCROSS_H
#define GUNCROSS_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT GunCross : public QGraphicsItem
{
public:
    GunCross();
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    const float m_lineWidth = 20;
};
#endif // GUNCROSS_H
