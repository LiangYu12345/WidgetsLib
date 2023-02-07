#ifndef MULTILELISTVIEW_H
#define MULTILELISTVIEW_H

#include "widgetslib_global.h"
#include <QListView>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QVector3D>
#include <QGeoCoordinate>

class MultileListViewItem;

/// 地图列表
/// 飞机  编号 名称 经度 纬度 高度 方位 俯仰 滚转角 速度
/// 区域
///
/// 圆形：编号 名称 中心点  水平半径  垂直半径  面积
/// 矩形：编号 名称 中心点  宽 高   面积
/// 多边形： 编号 名称  多个点 （经度 纬度 高度）
class WIDGETSLIB_EXPORT MultileListView : public QListWidget
{
    Q_OBJECT
public:
    struct AreaPayload{
        struct FlightPayload{
            char name[10];
            int  id;
            double lon;
            double lat;
            double alt;
            double yaw;
            double pitch;
            double roll;
        };
        struct EllipsePayload{
            char name[10];
            int id;
            double lon;
            double lat;
            double alt;
            double hRadiu;
            double vRadiu;
            double area;
        };
        struct RectPayload{
            char name[10];
            int id;
            double lon;
            double lat;
            double alt;
            double width;
            double height;
            double area;
        };
        struct PolygonPayload{
            char name[10];
            int id;
            int pointCount;
            double lon[20];
            double lat[20];
            double alt[20];
        };
        union ListViewPayload{
            FlightPayload  flight;
            EllipsePayload ellipse;
            RectPayload    rect;
            PolygonPayload polygon;
        };
        int type = 0;
        ListViewPayload listView;
    };
public:
    explicit MultileListView(QWidget * parent = nullptr);

    MultileListViewItem * addItem(int Index, const QString &name, const QPixmap &pixmap);
    MultileListViewItem * appendItem(const QString &name, const QPixmap &pixmap);
    void removeItem(int Index);

    void setMultileListViewItemData(int, AreaPayload &pay);
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent * e) override;
    virtual void leaveEvent(QEvent * e) override;
signals:
    void listItemEntered(MultileListViewItem *item);
    void listItemChanged(MultileListViewItem *pre, MultileListViewItem *cur);
    void listItemMoved(QPoint pos);
    void listItemLeaved();
    void listLeaved();

    void listFlightDoubleClicked(AreaPayload::FlightPayload pay);
    void listEllipseDoubleClicked(AreaPayload::EllipsePayload pay);
    void listRectDoubleClicked(AreaPayload::RectPayload pay);
    void listPolygonDoubleClicked(AreaPayload::PolygonPayload pay);
private:
    bool m_isItemHover;
    MultileListViewItem *m_previous;
    MultileListViewItem *m_current;
};

#endif // MULTILELISTVIEW_H
