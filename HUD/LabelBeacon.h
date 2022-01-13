#ifndef LABELBEACON_H
#define LABELBEACON_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT LabelBeacon : public QGraphicsItem
{
public:
    LabelBeacon();
    void setValue(QString value);
    void setDirection(int direction);  // 1 上 2 下 3 左 4 右
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QString m_value;
    int m_direction = 1;
    const float m_lineWidth = 40;
};
#endif // LABELBEACON_H
