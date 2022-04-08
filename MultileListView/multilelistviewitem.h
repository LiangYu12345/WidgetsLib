#ifndef MULTILELISTVIEWITEM_H
#define MULTILELISTVIEWITEM_H

#include "widgetslib_global.h"
#include <QListWidgetItem>

class WIDGETSLIB_EXPORT MultileListViewItem : public QListWidgetItem
{
public:
    MultileListViewItem(QListWidget * parent = nullptr);
};

#endif // MULTILELISTVIEWITEM_H
