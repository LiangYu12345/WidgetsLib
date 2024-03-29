﻿#ifndef PRELAUNCHAIM9TIMEOFFLIGHT_H
#define PRELAUNCHAIM9TIMEOFFLIGHT_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT PrelaunchAim9TimeOfFlight : public QGraphicsItem
{
public:
    PrelaunchAim9TimeOfFlight();
    void setValue(QString value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QString m_value = u8"06";
    const float m_textWidth = 40;
};
#endif // PRELAUNCHAIM9TIMEOFFLIGHT_H
