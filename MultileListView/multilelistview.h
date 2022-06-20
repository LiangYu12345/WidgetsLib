#ifndef MULTILELISTVIEW_H
#define MULTILELISTVIEW_H

#include "widgetslib_global.h"
#include <QListView>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QVector3D>
#include "multilelistviewitem.h"

/// 地图列表
/// 飞机  编号 名称 经度 维度 高度 方位 俯仰 滚转角 速度
/// 区域
///
/// 圆形：编号 名称 中心点  水平半径  垂直半径  面积
/// 矩形：编号 名称 中心点  宽 高   面积
/// 多边形： 编号 名称  多个点 （经度 维度 高度）
class WIDGETSLIB_EXPORT MultileListView : public QListWidget
{
    struct Position
    {
        double lat;     //纬度：北纬为正
        double lon;     //经度：东经为正
        double alt;     //海拔：米
    };

    struct Euler{
        double yaw;     //航向
        double pitch;   //俯仰
        double roll;    //滚转
    };

    struct FlightPayload{
        int       id;
        QString   name;
        Position  position;
        Euler     euler;
        double    speed;
    };

    struct EllipsePayload{
        int       id;
        QString   name;
        Position  center;
        double    hRadiu;
        double    vRadiu;
        double    area;
    };

    struct RectPayload{
        int       id;
        QString   name;
        Position  center;
        double    height;
        double    width;
        double    area;
    };

    struct PolygonPayload{
        struct Point{
            Position coord;
        };
        int       id;
        QString   name;
        int       count;
        Point     points[20];
    };
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

    void listItemClicked();
private:
    bool m_isItemHover;
    MultileListViewItem *m_previous;
    MultileListViewItem *m_current;
};

#endif // MULTILELISTVIEW_H
