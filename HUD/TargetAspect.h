#ifndef TARGETASPECT_H
#define TARGETASPECT_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT TargetAspect : public QGraphicsItem
{
public:
    TargetAspect();
    void setValue(QString value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QString m_value;
    const float m_lineLen = 20;
    float m_radius = 20;
};
#endif // TARGETASPECT_H
