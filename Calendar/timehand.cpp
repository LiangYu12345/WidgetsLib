#include "timehand.h"
#include <QPainter>
#include <QtMath>
#include <QVector3D>
#include <QDebug>
TimeHand::TimeHand(QGraphicsWidget *parent)
    : QGraphicsWidget{parent}
{
    m_isDrop = false;
}

void TimeHand::setHandPoints(QVector<QPoint> points)
{
    if(m_handPoints == points)
        return;
    m_handPoints = points;

    m_polygon.clear();
    for(auto item : qAsConst(m_handPoints))
        m_polygon.append(item);
    auto rect = m_polygon.boundingRect();

    resize(rect.width(), rect.height());
    /// 重置旋转中心点s
    this->setTransformOriginPoint(rect.width() / 2, rect.height() * 4 / 5);
}

void TimeHand::setHandColor(const QColor &color)
{
    m_color = color;
}

void TimeHand::setDrop(bool drop)
{
    m_isDrop = drop;
}

void TimeHand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    if(m_isDrop){
        painter->save();

        QPen pen;
        pen.setColor(QColor(255, 0, 0));

        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->setBrush(m_color);

        painter->drawConvexPolygon(m_polygon);
        painter->restore();
    }
    else{
        painter->setPen(Qt::NoPen);
        painter->setBrush(m_color);

        painter->drawConvexPolygon(m_polygon);
    }
}

void TimeHand::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_isDrop)
        return;

    m_isLeftMousePress = true;
    m_pressPoint = event->pos();
}

/*
 * 计算上一次鼠标移动和本次鼠标移动位置之间的角度。
    计算旋转的方向。
    根据计算的角度和方向，计算真正的选中角度（顺时针为正，逆时针为负）。
*/
void TimeHand::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_isLeftMousePress){

        // 通过向量的 点乘 ，计算角度。单位向量点乘的值，正好为角度的余弦
        auto point = QPointF(this->rect().width() / 2, this->rect().height() * 4 / 5);

        QVector2D startVec(m_pressPoint.x() - point.x(), m_pressPoint.y() - point.y());
        startVec.normalize();
        QVector2D endVec(event->pos().x() - point.x(), event->pos().y() - point.y());
        endVec.normalize();
        // 通过向量的 叉乘 ，计算旋转的方向。叉乘的结果为与这两个向量垂直的向量，可以通过Z轴结果判断，如果结果为正表示顺时针，结果为负表示逆时针。
        auto dotValue = QVector2D::dotProduct(startVec, endVec);
        if(dotValue > 1.0)
            dotValue = 1.0;
        else if(dotValue < -1.0)
            dotValue = -1.0;

        dotValue = qAcos(dotValue);
        if(isnan(dotValue))
            dotValue = 0.0;

        auto angle = dotValue * 1.0 / (M_PI / 180);

        auto crossValue = QVector3D::crossProduct(QVector3D(startVec, 1.0), QVector3D(endVec, 1.0));

        if(crossValue.z() < 0)
            angle = -angle;

        emit mouseMoveAngle(angle);
    }
}

void TimeHand::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_isDrop = !m_isDrop;
    m_isLeftMousePress = false;

    update();
}

void TimeHand::resizeEvent(QGraphicsSceneResizeEvent *event)
{

}
