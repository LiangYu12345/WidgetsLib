#ifndef AAMISSILETYPE_H
#define AAMISSILETYPE_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT AAMissileType : public QGraphicsItem
{
public:
    AAMissileType();
    void setValue(double value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    double m_valuefirst = 0.88;
    double m_valuesecond = 4.1;
    double m_valuethird = 2;
    QString m_armtext = u8"ARM";
    QString m_srmtext = u8"SRM";
    const float m_textWidth = 40;
};
#endif // AAMISSILETYPE_H
