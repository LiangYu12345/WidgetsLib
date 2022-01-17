#ifndef MISSILERETICLE_H
#define MISSILERETICLE_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT MissileReticle : public QGraphicsItem
{
public:
    MissileReticle();
    void setValue(QString value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QString m_value;
    const float m_lineWidth = 20;
    float m_radius = 20;
};
#endif // MISSILERETICLE_H
