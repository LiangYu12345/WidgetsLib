#ifndef TARGETSLANTRANGE_H
#define TARGETSLANTRANGE_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT TargetSlantRange : public QGraphicsItem
{
public:
    TargetSlantRange();
    void setValueFirst(QString value);
    void setValueSecond(QString value);
    void setValueThird(QString value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QString m_valuefirst = u8"F001.2";
    QString m_valuesecond = u8"09:36";
    QString m_valuethird = u8"058>03";
    const float m_textWidth = 40;
};
#endif // TARGETSLANTRANGE_H
