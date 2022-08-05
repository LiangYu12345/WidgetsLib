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

    void setType(const int &type) { m_type = type; }
    const int getType() const { return m_type; }

    void setFlightPayload(int mnt, ListView::FlightPayload &payload);
    void setEllipsePayload(int mnt, ListView::EllipsePayload &payload);
    void setRectPayload(int mnt, ListView::RectPayload &payload);
    void setPolygonPayload(int mnt, ListView::PolygonPayload &payload);

    const ListView::FlightPayload getFlightPayload(int mnt) const;
    const ListView::EllipsePayload getEllipsePayload(int mnt) const;
    const ListView::RectPayload getRectPayload(int mnt) const;
    const ListView::PolygonPayload getPolygonPayload(int mnt) const;
private:
    int m_type;

    QMap<int, ListView::FlightPayload> m_flights;
    QMap<int, ListView::EllipsePayload> m_ellipses;
    QMap<int, ListView::RectPayload> m_rects;
    QMap<int, ListView::PolygonPayload> m_polygons;
};

#endif // MULTILELISTVIEWITEM_H
