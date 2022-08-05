#ifndef MULTILELISTVIEW_H
#define MULTILELISTVIEW_H

#include "widgetslib_global.h"
#include <QListView>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QVector3D>


class MultileListViewItem;

namespace ListView {

struct FlightPosition
{
    double lat;
    double lon;
    double alt;
};

struct FlightEuler{
    double yaw;
    double pitch;
    double roll;
};

struct FlightPayload{
    QString name;
    int  id;
    FlightPosition coord;
    FlightEuler euler;
    double speed;
};

struct EllipsePayload{
    QString name;
    int id;
    FlightPosition coord;
    double hRadiu;
    double vRadiu;
    double area;
};

struct RectPayload{
    QString name;
    int id;
    FlightPosition coord;
    double width;
    double height;
    double area;
};

struct PolygonPayload{
    QString name;
    int id;
    int pointCount;
};
};

/// 地图列表
/// 飞机  编号 名称 经度 维度 高度 方位 俯仰 滚转角 速度
/// 区域
///
/// 圆形：编号 名称 中心点  水平半径  垂直半径  面积
/// 矩形：编号 名称 中心点  宽 高   面积
/// 多边形： 编号 名称  多个点 （经度 维度 高度）
class WIDGETSLIB_EXPORT MultileListView : public QListWidget
{
    Q_OBJECT
public:
    explicit MultileListView(QWidget * parent = nullptr);

    void addItem(int Index, const QString &name, const QPixmap &pixmap);
    void appendItem(const QString &name, const QPixmap &pixmap);
    void removeItem(int Index);
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent * e) override;
    virtual void leaveEvent(QEvent * e) override;
    //virtual QSize sizeHint() const override;
signals:
    void listItemEntered(MultileListViewItem *item);
    void listItemChanged(MultileListViewItem *pre, MultileListViewItem *cur);
    void listItemMoved(QPoint pos);
    void listItemLeaved();
    void listLeaved();

    void listFlightDoubleClicked(ListView::FlightPayload pay);
    void listEllipseDoubleClicked(ListView::EllipsePayload pay);
    void listRectDoubleClicked(ListView::RectPayload pay);
    void listPolygonDoubleClicked(ListView::PolygonPayload pay);
private:
    bool m_isItemHover;
    MultileListViewItem *m_previous;
    MultileListViewItem *m_current;
};

#endif // MULTILELISTVIEW_H
