#include "multilelistviewitem.h"

MultileListViewItem::MultileListViewItem(QListWidget *parent, int type)
{
    QListWidgetItem(parent, type);
}

MultileListViewItem::MultileListViewItem(const QPixmap &icon, const QString &name, QListWidget *parent, int type)
{
    QListWidgetItem((QIcon)icon, name, parent, type);
}

MultileListViewItem::MultileListViewItem(const QString &text, QListWidget *parent, int type)
{
    QListWidgetItem(text, parent, type);
}

MultileListViewItem::MultileListViewItem(const MultileListViewItem &other)
{
    QListWidgetItem((QListWidgetItem)other);
}
