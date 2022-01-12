#ifndef PITCHATTITUDEBARS_H
#define PITCHATTITUDEBARS_H

#include "widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class PitchAttitudeBars : public QGraphicsItem
{
public:
    PitchAttitudeBars();
    void setValue(float value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_value;
    const float m_lineWidth = 20;
    const float m_textWidth = 40;
};
#endif // PITCHATTITUDEBARS_H
