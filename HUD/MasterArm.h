#ifndef MASTERARM_H
#define MASTERARM_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT MasterArm : public QGraphicsItem
{
public:
    MasterArm();
    void setValue(QString value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QString m_value;
    const float m_lineWidth = 20;
    const float m_textWidth = 40;
};
#endif // MASTERARM_H
