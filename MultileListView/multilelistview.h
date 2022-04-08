#ifndef MULTILELISTVIEW_H
#define MULTILELISTVIEW_H

#include "widgetslib_global.h"
#include <QListView>
#include <QListWidgetItem>
#include <QMouseEvent>

/// 地图列表
/// 飞机  编号 名称 经度 维度 高度 方位 俯仰 滚转角
/// 区域
///
/// 园形：编号 名称 中心点  水平半径  垂直半径
/// 矩形：编号 名称 中心点  宽 高
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
    virtual void mouseMoveEvent(QMouseEvent * e) override;
signals:
    void listItemEntered(QListWidgetItem *item, QPoint pos);
    void listItemChanged(QListWidgetItem *item);
    void listItemMoved(QPoint pos);
    void listItemLeaved();
private:
    bool isItemHover;
};

#endif // MULTILELISTVIEW_H
