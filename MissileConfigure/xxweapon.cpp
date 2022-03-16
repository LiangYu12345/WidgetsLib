#include "xxweapon.h"
#include <QPainter>

XXWeapon::XXWeapon(QWidget *parent)
    :Missile(parent)
{
    m_path.addEllipse(QRect(0,0,40,40));
}

void XXWeapon::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setWindow(0,0,40,40);

    if(m_checked){
        QPen pen(Qt::yellow,2,Qt::SolidLine);
        painter.setPen(pen);
    }
    else{
        QPen pen(Qt::white,2,Qt::DotLine);
        painter.setPen(pen);
    }

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(m_path);
}

void XXWeapon::mousePressEvent(QMouseEvent *e)
{
    m_checked =! m_checked;
    update();
}

void XXWeapon::mouseDoubleClickEvent(QMouseEvent *e)
{
    e->ignore();
}
