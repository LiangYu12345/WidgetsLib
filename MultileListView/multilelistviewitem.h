#ifndef MULTILELISTVIEWITEM_H
#define MULTILELISTVIEWITEM_H

#include "widgetslib_global.h"
#include <QListWidgetItem>


class WIDGETSLIB_EXPORT MultileListViewItem : public QListWidgetItem
{
    enum MyType{
        Flight,
        Ellipse,
        Rect,
        Polygon,
        UN
    };
public:
    MultileListViewItem(QListWidget * parent = nullptr, int type = UserType);

    MultileListViewItem(const QPixmap &icon, const QString &name, QListWidget *parent, int type = UserType);

    MultileListViewItem(const QString &text, QListWidget *parent = nullptr, int type = UserType);

    MultileListViewItem(const MultileListViewItem &other);

    void setType(const int &type) { m_type = type; }
    const int getType() const { return m_type; }
private:
    int m_type;
};

#endif // MULTILELISTVIEWITEM_H
