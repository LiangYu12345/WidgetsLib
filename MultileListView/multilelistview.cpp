#include "multilelistview.h"
#include <QPainter>
#include <QScroller>
#include <QDebug>

MultileListView::MultileListView(QWidget *parent)
    : QListWidget(parent),
      m_isItemHover(false)
{
    this->setMouseTracking(true);

    this->setViewMode(QListView::IconMode);
    this->setIconSize(QSize(150,150));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setHorizontalScrollMode(QListWidget::ScrollPerPixel);
    QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);

    connect(this,&MultileListView::itemActivated,this,[=](){qDebug()<<"active";});
    connect(this,&MultileListView::itemChanged,this,[=](){qDebug()<<"changed";});
}

void MultileListView::addItem(int Index, const QString &name, const QPixmap &pixmap)
{
    auto item = new QListWidgetItem;

    item->setIcon(pixmap);
    item->setText(name);
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);

    this->insertItem(Index, item);
}

void MultileListView::appendItem(const QString &name, const QPixmap &pixmap)
{
    auto item = new QListWidgetItem(this);

    item->setIcon(pixmap);
    item->setText(name);
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
}

void MultileListView::removeItem(int Index)
{
    this->takeItem(Index);
}

void MultileListView::mouseMoveEvent(QMouseEvent *e)
{
    auto item = static_cast<QListWidgetItem *>(itemAt(e->pos()));

    if(item == nullptr && !m_isItemHover)
        return;
    else if(item == nullptr && m_isItemHover){
        m_isItemHover = false;
    }

    if(m_previous == nullptr && m_current == nullptr && m_isItemHover == false){
        m_current = item;
        emit listItemEntered(item, e->pos());
    }
    else if(m_previous == nullptr && m_current != nullptr){
        m_previous = m_current;
        m_isItemHover = true;
        emit listItemMoved(e->pos());
    }
    else if(m_previous != nullptr && m_current != nullptr && m_isItemHover == true){
        emit listItemMoved(e->pos());
    }
    else if(m_previous != nullptr && m_current != nullptr && m_isItemHover == false){
        m_current = nullptr;
        emit listItemLeaved();
    }
    else if(m_previous != nullptr && m_current == nullptr){
        m_previous =  nullptr;
    }
    QListWidget::mouseMoveEvent(e);
}

void MultileListView::leaveEvent(QEvent *e)
{
    emit listLeaved();
}
