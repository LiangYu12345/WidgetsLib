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

void MultileListViewItem::setFlightPayload(int mnt, ListView::FlightPayload &payload)
{
    if(m_flights.contains(mnt))
        return;
    m_flights.insert(mnt, payload);
}

void MultileListViewItem::setEllipsePayload(int mnt, ListView::EllipsePayload &payload)
{
    if(m_ellipses.contains(mnt))
        return;
    m_ellipses.insert(mnt, payload);
}

void MultileListViewItem::setRectPayload(int mnt, ListView::RectPayload &payload)
{
    if(m_rects.contains(mnt))
        return;
    m_rects.insert(mnt, payload);
}

void MultileListViewItem::setPolygonPayload(int mnt, ListView::PolygonPayload &payload)
{
    if(m_polygons.contains(mnt))
        return;
    m_polygons.insert(mnt, payload);
}

const ListView::FlightPayload MultileListViewItem::getFlightPayload(int mnt) const
{
    return m_flights.value(mnt);
}

const ListView::EllipsePayload MultileListViewItem::getEllipsePayload(int mnt) const
{
    return m_ellipses.value(mnt);
}

const ListView::RectPayload MultileListViewItem::getRectPayload(int mnt) const
{
    return m_rects.value(mnt);
}

const ListView::PolygonPayload MultileListViewItem::getPolygonPayload(int mnt) const
{
    return m_polygons.value(mnt);
}
