#ifndef SOISYMBOL_H
#define SOISYMBOL_H

#include "../widgetslib_global.h"

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QFont>

/*!
 * \brief The Crosshair class
 */
class WIDGETSLIB_EXPORT SoiSymbol : public QGraphicsItem
{
public:
    SoiSymbol();
    void setVisible(bool visible);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    bool m_visible;
    const float m_lineWidth = 20;
};
#endif // SOISYMBOL_H
