#include "drawerwidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QDebug>

DrawerWidget::DrawerWidget(QWidget *parent) : QWidget{parent},
    m_content(nullptr)
{
    m_button = new QPushButton(this);
    m_anim = new QPropertyAnimation(this, "pos", this);
    m_anim->setEasingCurve(QEasingCurve::OutCubic);
    m_anim->setDuration(500);

    connect(m_button, &QPushButton::clicked, this, &DrawerWidget::toggle);
}

void DrawerWidget::setAlignment(const QPoint &pos, Qt::Alignment align)
{
    m_basePos = pos;
    m_align = align;
    updateLayout();
    if(m_isOpened)
        open();
    else
        close();
}

void DrawerWidget::setText(const QString &text)
{
    m_button->setText(text);
    updateLayout();
}

void DrawerWidget::setIcon(const QIcon &icon)
{
    m_button->setIcon(icon);
    updateLayout();
}

void DrawerWidget::setContent(QWidget *widget)
{
    m_content = widget;
    m_content->setParent(this);
    updateLayout();
}

void DrawerWidget::open()
{
    m_isOpened = true;

    auto btnSize= m_button->sizeHint();
    auto btnWidth = btnSize.width();
    auto btnHeight = btnSize.height();
    auto width = this->width();
    auto height = this->height();

    QPoint startPos;
    QPoint endPos;
    switch (m_align) {
    case Qt::AlignLeft: {
        startPos = m_basePos - QPoint(btnWidth, 0);
        endPos = m_basePos - QPoint(width, 0);
    } break;
    case Qt::AlignRight: {
        startPos = m_basePos - QPoint(width - btnWidth, 0);
        endPos = m_basePos;
    } break;
    case Qt::AlignTop: {
        startPos = m_basePos - QPoint(0, btnHeight);
        endPos = m_basePos - QPoint(0, height);
    } break;
    case Qt::AlignBottom: {
        startPos = m_basePos - QPoint(0, height - btnHeight);
        endPos = m_basePos;
    } break;
    }

    m_anim->setStartValue(startPos);
    m_anim->setEndValue(endPos);
    m_anim->start();
}

void DrawerWidget::close()
{
    m_isOpened = false;

    auto btnSize= m_button->sizeHint();
    auto btnWidth = btnSize.width();
    auto btnHeight = btnSize.height();
    auto width = this->width();
    auto height = this->height();

    QPoint startPos;
    QPoint endPos;
    switch (m_align) {
    case Qt::AlignLeft: {
        startPos = m_basePos - QPoint(width, 0);
        endPos = m_basePos - QPoint(btnWidth, 0);
    } break;
    case Qt::AlignRight: {
        startPos = m_basePos;
        endPos = m_basePos - QPoint(width - btnWidth, 0);
    } break;
    case Qt::AlignTop: {
        startPos = m_basePos - QPoint(0, height);
        endPos = m_basePos - QPoint(0, btnHeight);
    } break;
    case Qt::AlignBottom: {
        startPos = m_basePos;
        endPos = m_basePos - QPoint(0, height - btnHeight);
    } break;
    }

    m_anim->setStartValue(startPos);
    m_anim->setEndValue(endPos);
    m_anim->start();
}

void DrawerWidget::toggle()
{
    if(m_isOpened)
        close();
    else
        open();
}


void DrawerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void DrawerWidget::updateLayout()
{
    auto btnSize= m_button->sizeHint();
    auto btnWidth = btnSize.width();
    auto btnHeight = btnSize.height();
    auto width = this->width();
    auto height = this->height();
    switch (m_align) {
    case Qt::AlignLeft: {
        m_button->setGeometry(0, (height - btnHeight)/2, btnWidth, btnHeight);
        if(m_content) m_content->setGeometry(btnWidth, 0, width, height);
    } break;
    case Qt::AlignRight: {
        if(m_content) m_content->setGeometry(0, 0, width-btnWidth, height);
        m_button->setGeometry(width-btnWidth, (height - btnHeight)/2, btnWidth, btnHeight);
    } break;
    case Qt::AlignTop: {
        m_button->setGeometry((width-btnWidth)/2, 0, btnWidth, btnHeight);
        if(m_content) m_content->setGeometry(0, btnHeight, width, height-btnHeight);
    } break;
    case Qt::AlignBottom: {
        if(m_content) m_content->setGeometry(0, 0, width, height-btnHeight);
        m_button->setGeometry((width-btnWidth)/2, height-btnHeight, btnWidth, btnHeight);
    } break;
    }
}
