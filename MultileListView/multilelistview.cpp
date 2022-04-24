#include "multilelistview.h"
#include <QPainter>
#include <QScroller>
#include <QDebug>

MultileListView::MultileListView(QWidget *parent)
    : QListWidget(parent),
      m_isItemHover(false),
      m_previous(nullptr),
      m_current(nullptr)
{
    this->setMouseTracking(true);

    this->setViewMode(QListView::IconMode);
    this->setWrapping(false);
    this->setFlow(QListView::LeftToRight);
    this->setIconSize(QSize(150, 150));
    //this->resize(QSize(600, 100));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setHorizontalScrollMode(QListWidget::ScrollPerPixel);
    QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);

    connect(this,&MultileListView::itemEntered,this,[=](QListWidgetItem *item){ m_isItemHover = true; m_current = item; emit listItemEntered(item);});
    connect(this,&MultileListView::listLeaved,this,[=](){ m_isItemHover = false; emit listItemLeaved();});

    connect(this,&MultileListView::currentItemChanged,this,[=](QListWidgetItem *pre,QListWidgetItem *cur){
        emit listItemChanged(pre, cur);
    });
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
    delete this->takeItem(Index);
}

void MultileListView::mouseMoveEvent(QMouseEvent *e)   // 需判断前后的Item 是否发生改变，
{
    auto item = dynamic_cast<QListWidgetItem *>(itemAt(e->pos()));

    // 判断item 是否改变
    if(item != m_current){
        m_previous = m_current;
        m_current = item;
        emit listItemChanged(m_previous, m_current);

        // 改变之后 判断是否重新进入同一个Item
        // (Note: 进入一个Item 再移出当前Item 现指向null 再重新移入那个Item QListWidget没有识别重新进入Item,因为QListWidget没有leaveItem的信号)
        if(item != nullptr)
            emit listItemEntered(item);
    }

    if(item == nullptr && !m_isItemHover)
        return;
    else if(item == nullptr && m_isItemHover){
        m_current = item;
        emit listItemLeaved();
        return;
    }

    if(m_isItemHover){
        emit listItemMoved(e->pos());
    }

    QListWidget::mouseMoveEvent(e);
}

void MultileListView::leaveEvent(QEvent *e)
{
    // 针对移出窗口时 没经过listItemLeaved
    m_previous = m_current;
    m_current = nullptr;
    emit listItemChanged(m_previous, m_current);

    emit listLeaved();
}
