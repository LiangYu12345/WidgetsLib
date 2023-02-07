#include "drawerpanel.h"
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QtMath>

DrawerPanel::DrawerPanel(QWidget *parent) : QWidget{parent},
    m_align(Qt::AlignRight),
    m_content(nullptr)
{
    m_button = new QToolButton(this);
    m_anim = new QPropertyAnimation(this, "pos", this);
    m_anim->setEasingCurve(QEasingCurve::OutCubic);
    m_anim->setDuration(500);

    connect(m_button, &QToolButton::clicked, this, &DrawerPanel::toggle);
}

void DrawerPanel::setAlignment(const QPoint &pos, Qt::Alignment align)
{
    m_basePos = pos;
    m_align = align;
    updateLayout();

    this->move(computePos(m_isOpened, align));
}

void DrawerPanel::setText(const QString &text)
{
    m_button->setText(text);
    updateLayout();
}

void DrawerPanel::setIcon(const QIcon &icon)
{
    m_button->setIcon(icon);
    switch (m_align) {
    case Qt::AlignLeft:
    case Qt::AlignRight:
        m_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        break;
    case Qt::AlignTop:
    case Qt::AlignBottom:
        m_button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        break;
    }
    updateLayout();
}

void DrawerPanel::setContent(QWidget *widget)
{
    m_content = widget;
    m_content->setParent(this);
    updateLayout();
}

QWidget *DrawerPanel::content() const
{
    return m_content;
}

void DrawerPanel::open()
{
    if(m_isOpened)
        return;
    m_isOpened = true;

    QPoint startPos = computePos(false, m_align);
    QPoint endPos = computePos(true, m_align);

    m_anim->setStartValue(startPos);
    m_anim->setEndValue(endPos);
    m_anim->start();
}

void DrawerPanel::close()
{
    if(!m_isOpened)
        return;
    m_isOpened = false;

    QPoint startPos = computePos(true, m_align);
    QPoint endPos = computePos(false, m_align);

    m_anim->setStartValue(startPos);
    m_anim->setEndValue(endPos);
    m_anim->start();
}

void DrawerPanel::toggle()
{
    if(m_isOpened)
        close();
    else
        open();
}

void DrawerPanel::updateLayoutInterface()
{
    this->updateLayout();
}

QSize DrawerPanel::sizeHint() const
{
    QSize size;
    auto buttonSizeHint = m_button->sizeHint();
    auto contentSizeHint = m_content ? m_content->sizeHint() : buttonSizeHint;
    switch (m_align) {
    case Qt::AlignLeft:
    case Qt::AlignRight: {
        size = {contentSizeHint.width() + buttonSizeHint.width(), qMax(buttonSizeHint.height(), contentSizeHint.height())};
    } break;
    case Qt::AlignTop:
    case Qt::AlignBottom: {
        size = {qMax(buttonSizeHint.width(), contentSizeHint.width()), buttonSizeHint.height() + contentSizeHint.height()};
    } break;
    }
    return size;
}


void DrawerPanel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void DrawerPanel::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateLayout();
    this->move(computePos(m_isOpened, m_align));
}

QPoint DrawerPanel::computePos(bool open, Qt::Alignment align)
{
    auto btnSize= m_button->sizeHint();
    auto btnWidth = btnSize.width();
    auto btnHeight = btnSize.height();
    auto width = this->width();
    auto height = this->height();

    QPoint pos;
    if(open) {
        switch (align) {
        case Qt::AlignLeft: {
            pos = m_basePos - QPoint(width, 0);
        } break;
        case Qt::AlignRight: {
            pos = m_basePos;
        } break;
        case Qt::AlignTop: {
            pos = m_basePos - QPoint(0, height);
        } break;
        case Qt::AlignBottom: {
            pos = m_basePos;
        } break;
        }
    }
    else {  // close
        switch (align) {
        case Qt::AlignLeft: {
            pos = m_basePos - QPoint(btnWidth, 0);
        } break;
        case Qt::AlignRight: {
            pos = m_basePos - QPoint(width - btnWidth, 0);
        } break;
        case Qt::AlignTop: {
            pos = m_basePos - QPoint(0, btnHeight);
        } break;
        case Qt::AlignBottom: {
            pos = m_basePos - QPoint(0, height - btnHeight);
        } break;
        }
    }

    return pos;
}

void DrawerPanel::updateLayout()
{
    auto btnSize= m_button->sizeHint();
    auto btnWidth = btnSize.width();
    auto btnHeight = btnSize.height();
    auto width = this->width();
    auto height = this->height();
    switch (m_align) {
    case Qt::AlignLeft: {
        m_button->setGeometry(0, (height - btnHeight)/2, btnWidth, btnHeight);
        if(m_content) m_content->setGeometry(btnWidth, 0, width - btnWidth, height);
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
