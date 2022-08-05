#include "multilelistview.h"
#include <QPainter>
#include <QScroller>
#include <QDebug>
#include "multilelistviewitem.h"

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
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setHorizontalScrollMode(QListWidget::ScrollPerPixel);
    QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);

    connect(this,&MultileListView::itemEntered,this,[=](QListWidgetItem *item){ m_isItemHover = true; m_current = (MultileListViewItem*)item; emit listItemEntered(m_current);});
    connect(this,&MultileListView::listLeaved,this,[=](){ m_isItemHover = false; emit listItemLeaved();});

    connect(this,&MultileListView::currentItemChanged,this,[=](QListWidgetItem *pre,QListWidgetItem *cur){
        emit listItemChanged((MultileListViewItem*)pre, (MultileListViewItem*)cur);
    });
}

void MultileListView::addItem(int Index, const QString &name, const QPixmap &pixmap)
{
    MultileListViewItem * item =  nullptr;
    if(name == "J20"){
        item = new MultileListViewItem(pixmap, name, this);
        item->setType(1);
        ListView::FlightPayload pay;
        pay.name = name;
        pay.id = 1;
        pay.coord = {1.0,2.0,3.0};
        item->setFlightPayload(0, pay);
    }
    else if(name == "F35"){
        item = new MultileListViewItem(pixmap, name, this);
        item->setType(2);
    }
    else if(name == u8"圆形"){
        item = new MultileListViewItem(pixmap, name, this);
        item->setType(3);
    }
    else if(name == u8"矩形"){
        item = new MultileListViewItem(pixmap, name, this);
        item->setType(4);
    }
    else if(name == u8"多边形"){
        item = new MultileListViewItem(pixmap, name, this);
        item->setType(5);
    }

    item->setIcon(pixmap);
    item->setText(name);
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);

    qDebug()<<item->getType() << item->type() << item->Type << item->UserType;

    this->insertItem(Index, item);
}

void MultileListView::appendItem(const QString &name, const QPixmap &pixmap)
{
    auto count = this->count();
    MultileListViewItem * item =  nullptr;
    if(name == "J20"){
        item = new MultileListViewItem(pixmap, name, this);
        item->setType(1);
    }
    else if(name == "F35"){
        item = new MultileListViewItem(pixmap, name, this);
        item->setType(2);
    }
    else if(name == u8"圆形"){
        item = new MultileListViewItem(pixmap, name, this);
        item->setType(3);
    }
    else if(name == u8"矩形"){
        item = new MultileListViewItem(pixmap, name, this);
        item->setType(4);
    }
    else if(name == u8"多边形"){
        item = new MultileListViewItem(pixmap, name, this);
        item->setType(5);
    }

    item->setIcon(pixmap);
    item->setText(name);
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);

    this->insertItem(count, item);
}

void MultileListView::removeItem(int Index)
{
    delete this->takeItem(Index);
}

void MultileListView::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto item = (MultileListViewItem *)itemAt(event->pos());
    if(item == nullptr)
        return;

    if(item->getType() == 1){
        qDebug()<<u8"J20"<<item->getType();
        emit listFlightDoubleClicked(item->getFlightPayload(0));
    }
    else if(item->getType() == 2){
        qDebug()<<u8"F35"<<item->getType();
        emit listFlightDoubleClicked(item->getFlightPayload(0));
    }
    else if(item->getType() == 3){
        qDebug()<<u8"圆"<<item->getType();
    }
    else if(item->getType() == 4){
        qDebug()<<u8"矩形"<<item->getType();
    }
    else if(item->getType() == 5){
        qDebug()<<u8"多边形"<<item->getType();
    }
}

void MultileListView::mouseMoveEvent(QMouseEvent *e)   // 需判断前后的Item 是否发生改变，
{
    auto item = dynamic_cast<MultileListViewItem *>(itemAt(e->pos()));

    // 判断item 是否改变
    if(item != m_current){
        m_previous = m_current;
        m_current = item;
        emit listItemChanged(m_previous, m_current);

        // 改变之后 判断是否重新进入同一个Item
        // (Note: 进入一个Item 再移出当前Item 现指向null 再重新移入那个Item QListWidget没有识别重新进入Item,因为QListWidget没有leaveItem的信号)
        //if(item != nullptr)
        //   emit listItemEntered(item);
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

//QSize MultileListView::sizeHint() const
//{
//    qDebug()<<this->count()<<"listWidgetCount";
//    return QSize();
//}
