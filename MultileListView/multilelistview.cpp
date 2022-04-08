#include "multilelistview.h"
#include <QPainter>
#include <QScroller>
#include <QDebug>

MultileListView::MultileListView(QWidget *parent)
    : QListWidget(parent)
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

    if(item == nullptr)
        return;
    emit listItemMoved(e->pos());
    QListWidget::mouseMoveEvent(e);
}
