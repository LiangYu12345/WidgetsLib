#include "f35frontview.h"
#include <QPainter>

F35FrontView::F35FrontView(QWidget *parent)
{
    m_path.moveTo(0,3);
    m_path.cubicTo(QPointF(),QPointF(),QPointF(-24,11));
    m_path.cubicTo(QPointF(),QPointF(),QPointF(-34,25));
    m_path.cubicTo(QPointF(),QPointF(),QPointF(-45,31));
    m_path.lineTo(-60,1);
    m_path.lineTo(-52,33);
    m_path.lineTo(-175,37);
    m_path.lineTo(-175,42);
    m_path.lineTo(-80,45);
    m_path.cubicTo(QPointF(),QPointF(),QPointF(-73,52));

    m_path.lineTo(3,3);
    m_path.cubicTo(QPointF(),QPointF(),QPointF());
    m_path.lineTo(4,4);
}

void F35FrontView::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setWindow(-180,0,360,80);

    QPen pen(m_painterColor,2);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(m_path);

    QTransform trans = painter.transform();
    painter.setTransform(trans.rotate(180,Qt::YAxis));

    painter.drawPath(m_path);
}

void F35FrontView::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void F35FrontView::resizeEvent(QResizeEvent *e)
{

}

QSize F35FrontView::sizeHint() const
{
    return QSize(360,80);
}

void F35FrontView::replaceMissie(int mount, Missile *curMissile)
{

}

void F35FrontView::updateLayout()
{

}
