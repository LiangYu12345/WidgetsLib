#ifndef AITITUDELOWSETTING_H
#define AITITUDELOWSETTING_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT AltitudeLowSetting : public QGraphicsItem
{
public:
    AltitudeLowSetting();
    void setValue(float value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    float m_value;
    const float m_textWidth = 40;
};
#endif // AITITUDELOWSETTING_H
