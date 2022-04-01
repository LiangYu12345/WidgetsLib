#include "f35frontview.h"
#include <QPainter>

F35FrontView::F35FrontView(QWidget *parent)
    :WeaponConfigure(parent)
{
    m_path.moveTo(0,40);
    m_path.cubicTo(QPointF(-12,40),QPointF(-12,53),QPointF(-12,53));
    m_path.cubicTo(QPointF(-12,49),QPointF(-28,65),QPointF(-36,65));
    m_path.lineTo(-38,64);
    m_path.lineTo(-64,1);
    m_path.lineTo(-43,66);
    m_path.lineTo(-179,69);
    m_path.lineTo(-179,72);
    m_path.lineTo(-64,75);
    m_path.lineTo(-60,80);
    m_path.lineTo(-50,82);
    m_path.cubicTo(QPointF(-35,82),QPointF(-35,93),QPointF(-35,93));
    m_path.lineTo(-26,93);
    m_path.lineTo(-22,91);
    m_path.lineTo(-18,93);
    m_path.lineTo(-8,93);
    m_path.cubicTo(QPointF(-8,93),QPointF(-8,99),QPointF(-0,99));
}

void F35FrontView::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setWindow(-180,0,360,100);

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
    return QSize(360,100);
}
