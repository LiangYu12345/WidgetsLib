#include "switchbutton.h"
#include <QPainter>

SwitchButton::SwitchButton(QWidget *parent)  //fix时间移动完全程 （待改）
    : QWidget(parent),
      m_height(16),
      m_radius(8.0),
      m_marigin(3),
      m_checkedColor(0,150,136),
      m_thumbColor(Qt::white),
      m_disabledColor(190,190,190),
      m_backgroundColor(Qt::black),
      m_timetotal(250),
      m_actortime(0),
      m_checked(false),
      m_interval(17)
{
    connect(&m_timer,&QTimer::timeout,this,&SwitchButton::onTimeout);
}

SwitchButton::SwitchButton(const QString &opentext, const QString &closetext, QWidget *parent)
    :QWidget(parent)
{
    m_opentext = opentext;
    m_closetext = closetext;
    connect(&m_timer,&QTimer::timeout,this,&SwitchButton::onTimeout);
}

void SwitchButton::setToggle(bool checked)
{
    m_checked = checked;
    m_timer.start(m_interval);
}

void SwitchButton::setBackgroundColor(QColor color)
{
    m_backgroundColor = color;
}

void SwitchButton::setCheckedColor(QColor color)
{
    m_checkedColor = color;
}

void SwitchButton::setDisabledColor(QColor color)
{
    m_disabledColor = color;
}

void SwitchButton::setChangedTimeTotal(const double &value)
{
    m_timetotal = value;
}

void SwitchButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    QColor backgroundColor;
    QColor thumbColor;
    double Opacity;
    if(isEnabled()){
        if(m_checked){
            backgroundColor = m_checkedColor;
            thumbColor = m_checkedColor;
            Opacity = 0.6;
        }else{
            backgroundColor = m_backgroundColor;
            thumbColor = m_thumbColor;
            Opacity = 0.8;
        }
    }else{
        backgroundColor = m_backgroundColor;
        Opacity = 0.26;
        thumbColor = m_disabledColor;
    }

    painter.setBrush(backgroundColor);
    painter.setOpacity(Opacity);
    path.addRoundedRect(QRect(m_marigin,m_marigin,width() - 2*m_marigin, height() - 2*m_marigin),m_radius,m_radius);
    painter.drawPath(path.simplified());

    painter.setBrush(thumbColor);
    painter.setOpacity(1.0);
    painter.drawEllipse(QRectF((m_actortime/m_timetotal) * (width()-height()), 0 ,height(),height()));

}

void SwitchButton::mousePressEvent(QMouseEvent *e)
{
    if(isEnabled()){
        if(e->buttons() & Qt::LeftButton){
            e->accept();
        }
        else
            e->ignore();
    }
}

void SwitchButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(isEnabled()){
        if(e->type() == QMouseEvent::MouseButtonRelease){
            e->accept();
            m_checked = !m_checked;
            emit checked(m_checked);
            m_timer.start(m_interval);
        }else{
            e->ignore();
        }
    }
}

void SwitchButton::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

QSize SwitchButton::sizeHint() const
{
    return QSize(60,27);
}

QSize SwitchButton::minimumSizeHint() const
{
    return QSize(60,27);
}

void SwitchButton::onTimeout()
{
    if(m_checked){
        m_actortime += m_timer.interval();
        if(m_actortime > m_timetotal){
            m_actortime = 250;
            m_timer.stop();
        }
    }else{
        m_actortime -= m_timer.interval();
        if(m_actortime < 0){
            m_actortime = 0;
            m_timer.stop();
        }
    }
    update();
}
