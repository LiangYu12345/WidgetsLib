﻿#ifndef HORIZONLINE_H
#define HORIZONLINE_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT HorizonLine : public QGraphicsItem
{
public:
    HorizonLine();
    void setInclinationAngleValue(float value);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    const float m_lineWidth = 20;
    double m_angle;
};
#endif // HORIZONLINE_H
