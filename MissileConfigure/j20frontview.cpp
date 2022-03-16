#include "j20frontview.h"
#include <QPainter>

J20FrontView::J20FrontView(QWidget *parent)
    :MissileConfigure(parent)
{
    m_path.moveTo(0,0);
    m_path.cubicTo(QPointF(-10,0),QPointF(-10,15),QPointF(-12,20));
    m_path.cubicTo(QPointF(-10,0),QPointF(-50,30),QPointF(-50,30));
    m_path.lineTo(-170,40);
    m_path.lineTo(-171,46);
    m_path.lineTo(-65,40);
    m_path.lineTo(-58,50);
    m_path.lineTo(-45,48);
    m_path.lineTo(-30,70);
    m_path.lineTo(0,70);
}

void J20FrontView::paintEvent(QPaintEvent *e)
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

void J20FrontView::mouseDoubleClickEvent(QMouseEvent *e)
{

}

void J20FrontView::resizeEvent(QResizeEvent *e)
{

}

QSize J20FrontView::sizeHint() const
{
    return QSize(360,80);
}

void J20FrontView::replaceMissie(int mount, Missile *curMissile)
{

}

void J20FrontView::updateLayout()
{

}
