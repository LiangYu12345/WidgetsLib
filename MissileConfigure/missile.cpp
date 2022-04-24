#include "missile.h"
#include <QPainter>
#include <QTimer>

Missile::Missile(QWidget *parent)
    : QWidget(parent),
      m_painterColor(Qt::white),
      m_checked(false)
{
    m_time = new QTimer;
    m_time->setInterval(200);
    connect(m_time,&QTimer::timeout, this, &Missile::singleClicked);
}

void Missile::paintEvent(QPaintEvent *e)
{
    e->accept();
}

void Missile::mousePressEvent(QMouseEvent *e)
{
    m_time->start();
}

void Missile::mouseDoubleClickEvent(QMouseEvent *e)
{
    m_time->stop();
    emit doubleClicked();
}

void Missile::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

QSize Missile::sizeHint() const
{
    return QSize(24,180);
}

void Missile::singleClicked()
{
    m_time->stop();
    m_checked =! m_checked;
    if(m_checked)
        m_painterColor = Qt::yellow;
    else
        m_painterColor = Qt::white;
    emit clicked(m_checked);
    update();
}
