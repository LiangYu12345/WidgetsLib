#include "radarmissile.h"
#include <QPainter>
#include <QTimer>

RadarMissile::RadarMissile(QWidget *parent)
    : Missile(parent)
{
    m_path.cubicTo(QPointF(-6,0),QPointF(-6,55),QPointF(-6,55));
    m_path.cubicTo(QPointF(0,54),QPointF(6,55),QPointF(6,55));
    m_path.moveTo(QPointF(-6,55));
    m_path.lineTo(-6,180);
    m_path.lineTo(0,180);
    m_path.moveTo(-6,65);
    m_path.lineTo(-12,95);
    m_path.lineTo(-6,92);
    m_path.moveTo(-6,148);
    m_path.lineTo(-10,154);
    m_path.lineTo(-12,175);
    m_path.lineTo(-6,174);

    this->setProperty("Type",Radar);
}

void RadarMissile::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setWindow(-12,0,24,180);


    QPen pen(m_painterColor,2);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(m_path);

    QTransform trans = painter.transform();
    painter.setTransform(trans.rotate(180,Qt::YAxis));

    painter.drawPath(m_path);
}
