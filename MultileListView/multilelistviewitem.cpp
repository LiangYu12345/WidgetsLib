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

void MultileListViewItem::setPayloadData(MultileListView::AreaPayload &payload)
{
    switch (payload.type) {
        case 1:{
            m_data.listView.flight = payload.listView.flight;
            m_type = 1;
            break;
        }
        case 2:{
            m_data.listView.ellipse = payload.listView.ellipse;
            m_type = 2;
            break;
        }
        case 3:{
            m_data.listView.rect = payload.listView.rect;
            m_type = 3;
            break;
        }
        case 4:{
            m_data.listView.polygon = payload.listView.polygon;
            m_type = 4;
            break;
        }
    }
}

const MultileListView::AreaPayload::FlightPayload MultileListViewItem::getFlightPayload() const
{
    return m_data.listView.flight;
}

const MultileListView::AreaPayload::EllipsePayload MultileListViewItem::getEllipsePayload() const
{
    return m_data.listView.ellipse;
}

const MultileListView::AreaPayload::RectPayload MultileListViewItem::getRectPayload() const
{
    return m_data.listView.rect;
}

const MultileListView::AreaPayload::PolygonPayload MultileListViewItem::getPolygonPayload() const
{
    return m_data.listView.polygon;
}
