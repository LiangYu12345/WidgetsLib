#ifndef TIMEHAND_H
#define TIMEHAND_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsWidget>
#include <QGraphicsItem>

class WIDGETSLIB_EXPORT TimeHand : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit TimeHand(QGraphicsWidget *parent = nullptr);

    void setHandPoints(QVector<QPoint> points);
    void setHandColor(const QColor &color);
    void setDrop(bool drop);
signals:
    void mouseMoveOffset(const QPointF &scenePos, const QPointF &loacalPos);
    void mouseMoveAngle(const int &angle);
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void resizeEvent(QGraphicsSceneResizeEvent *event) override;
private:
    QVector<QPoint>     m_handPoints;
    QPolygon            m_polygon;
    QColor              m_color;
    bool                m_isLeftMousePress; /// < 左键按下
    bool                m_isDrop;           /// < 拖拽
    QPointF             m_pressPoint;
};

#endif // TIMEHAND_H
