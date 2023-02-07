#ifndef MULTILELISTVIEWITEM_H
#define MULTILELISTVIEWITEM_H

#include "widgetslib_global.h"
#include "multilelistview.h"
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QVector3D>

class WIDGETSLIB_EXPORT MultileListViewItem : public QListWidgetItem
{

public:
    MultileListViewItem(QListWidget * parent = nullptr, int type = UserType);

    MultileListViewItem(const QPixmap &icon, const QString &name, QListWidget *parent, int type = UserType);

    MultileListViewItem(const QString &text, QListWidget *parent = nullptr, int type = UserType);

    MultileListViewItem(const MultileListViewItem &other);

    /// 设置List中的类型，按类型进行分类。 1 ： 飞机  2： 圆  3： 矩形  4： 多边形
    void setPayloadData(MultileListView::AreaPayload &payload);

    int getType() { return m_type; }

    const MultileListView::AreaPayload::FlightPayload getFlightPayload() const;
    const MultileListView::AreaPayload::EllipsePayload getEllipsePayload() const;
    const MultileListView::AreaPayload::RectPayload getRectPayload() const;
    const MultileListView::AreaPayload::PolygonPayload getPolygonPayload() const;
private:
    int m_type;
    MultileListView::AreaPayload m_data;
};

#endif // MULTILELISTVIEWITEM_H
