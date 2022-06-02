#ifndef LABELBEACONLINE_H
#define LABELBEACONLINE_H

#include "../widgetslib_global.h"
#include <QGraphicsPixmapItem>
#include <QPen>
#include <QBrush>
#include <QFont>

class WIDGETSLIB_EXPORT LabelBeaconLine : public QGraphicsItem
{
public:
    explicit LabelBeaconLine();

    void setTextVisible(bool visible);
    void setText(QString str);
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    bool m_visible;
    QString m_text;
};

#endif // LABELBEACONLINE_H
