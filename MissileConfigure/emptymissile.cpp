#include "emptymissile.h"
#include <QPainter>

EmptyMissile::EmptyMissile(QWidget *parent)
    : Missile(parent)
{
    m_path.cubicTo(QPointF(-6,0),QPointF(-6,55),QPointF(-6,55));
    m_path.cubicTo(QPointF(0,53),QPointF(6,55),QPointF(6,55));
    m_path.moveTo(QPointF(-6,55));
    m_path.lineTo(-6,180);
    m_path.lineTo(0,180);

    this->setProperty("Type",Empty);
}

void EmptyMissile::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setWindow(-12,0,24,180);


    QPen pen(Qt::white,2,Qt::DotLine);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(m_path);

    QTransform trans = painter.transform();
    painter.setTransform(trans.rotate(180,Qt::YAxis));

    painter.drawPath(m_path);
}

void EmptyMissile::mousePressEvent(QMouseEvent *e)
{
    e->ignore();
}

void EmptyMissile::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit doubleClicked();
}
