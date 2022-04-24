#include "j20frontview.h"
#include <QPainter>

J20FrontView::J20FrontView(QWidget *parent)
    :WeaponConfigure(parent)
{
    m_path.moveTo(0,36);
    m_path.cubicTo(QPointF(-8,36),QPointF(-15,52),QPointF(-15,52));
    m_path.cubicTo(QPointF(-15,48),QPointF(-54,59),QPointF(-54,59));
    m_path.lineTo(-78,1);
    m_path.lineTo(-58,59);
    m_path.lineTo(-106,52);
    m_path.lineTo(-80,60);
    m_path.lineTo(-170,66);
    m_path.lineTo(-171,70);
    m_path.lineTo(-66,66);
    m_path.lineTo(-63,69);
    m_path.lineTo(-74,94);
    m_path.lineTo(-60,70);
    m_path.lineTo(-50,71);
    m_path.lineTo(-36,95);
    m_path.lineTo(0,95);
}

void J20FrontView::paintEvent(QPaintEvent *e)
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

void J20FrontView::resizeEvent(QResizeEvent *e)
{

}

QSize J20FrontView::sizeHint() const
{
    return QSize(360,100);
}

void J20FrontView::mouseDoubleClickEvent(QMouseEvent *e)
{
    e->ignore();
}
