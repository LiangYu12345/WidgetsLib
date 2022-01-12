#ifndef RADARALTITUDE_H
#define RADARALTITUDE_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT RadarAltitude : public QGraphicsItem
{
public:
    RadarAltitude();
    void setValue(float value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_value;
    const float m_lineLen = 20;
    const float m_textWidth = 40;
};
#endif // RADARALTITUDE_H
