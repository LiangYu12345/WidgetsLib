#ifndef TARGETCLOSURERATE_H
#define TARGETCLOSURERATE_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT TargetClosureRate : public QGraphicsItem
{
public:
    TargetClosureRate();
    void setValue(double value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    double m_value = 750;
    const float m_textWidth = 40;
};
#endif // TARGETCLOSURERATE_H
