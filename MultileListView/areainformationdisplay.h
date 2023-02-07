#ifndef AREAINFORMATIONDISPLAY_H
#define AREAINFORMATIONDISPLAY_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGeoCoordinate>

/*!
 * \brief 列表信息窗口
 * \details 用于鼠标Hover显示列表的数据
 */
class WIDGETSLIB_EXPORT AreaInformationDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit AreaInformationDisplay(QWidget *parent = nullptr);

    void addItem(int Index, const QString &name, const QString &value);
    void appendItem(const QString &name, const QString &value);
    /// 当前GridLayout 暂无删除表格的网格  所以在此不做删除  该做隐藏(该函数不调用)
    void removeItem(int Index);
    void changeItem(int Index, const QString &name, const QString &value);
    void changeItemKey(int Index, const QString &name);
    void changeItemVal(int Index, const QString &value);

    /// int type 代表当前列表信息窗口显示的数据类型
    /// note: 1：J20   2：F35    3：圆形    4：矩形      5：多边形
    void chooseMode(const int &type);
    int currentMode() { return m_type; }
signals:

private:
    void dealRowCount(const int &value);
private:
    QGridLayout * m_gLayout;

    QLabel * m_numberLabelKey;
    QLabel * m_numberLabelVal;
    QLabel * m_nameLabelKey;
    QLabel * m_nameLabelVal;

    int m_type;
};

#endif // AREAINFORMATIONDISPLAY_H
