#ifndef DISTANCETOSTEERPOINT_H
#define DISTANCETOSTEERPOINT_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT DistanceToSteerpoint : public QGraphicsItem
{
public:
    DistanceToSteerpoint();
    void setValue(QString value);
    void setDisToValue(QString value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QString m_distovalue = "018";
    QString m_value = "03";
    const float m_lineWidth = 20;
    const float m_textWidth = 40;
};
#endif // DISTANCETOSTEERPOINT_H
