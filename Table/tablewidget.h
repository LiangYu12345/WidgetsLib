#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QMenu>
#include <QAction>

enum WidgetType{
    Text,Button,LineEdit,Icon
};

class PointsWidget : public QWidget
{
    Q_OBJECT

public:
    PointsWidget(int row,int column,QWidget *parent = nullptr);
    PointsWidget(QWidget *parent = nullptr);
    ~PointsWidget() override;
    //添加一列表头
    void appendHeader(QString name);
    //插入一列表头
    void insertHeader(int number,WidgetType type,QString name);
    //移除一列表头
    void removeHeader(int number);
    //获取当前行的数据
    QList<QTableWidgetItem *> m_points() const;
    //获取表格总行数
    int getRowCount() const;
    //编辑表格中一个Point的单个数据
    void editPoint(int row,int column,QString value);    // 差一个编辑表格中一个点的单个数据的数据类型：Icon，Btn
    //添加一行  默认为空
    void appendPoint();
    //插入至某行
    void insertPoint(int num);
    //移除某行
    void removePoint(int num);
    //清除所有数据
    void clearAll();
public slots:
    void slotBtnClicked();
    void slotLineEditTextChanged(QString text);
    void slotChooseCurrentPointChanged(QTableWidgetItem *current, QTableWidgetItem *previous);
signals:
    // 添加信号
    void signalAdd();
    //删除信号
    void signalRemoved();
    //编辑信号
    void signalEdit();
    //切换信号
    void signalSwitch();
    //当前点添加及插入信号
    void singalPointAdd();
    //当前点删除信号
    void signalPointRemove();
    //当前点修改信号
    void signalPointChange();
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
private:
    void Init();

    //表刷新 每个元素居中
    void Refresh();

    //构建按钮窗口
    QWidget * CreateBtnWdiget(const QString &btnname);
    //构建输入框窗口
    QWidget * CreateLineEditWdiget();
    //构建图片窗口
    QWidget * CreateIconWdiget(const QPixmap &pixmap);

    //插入单元格
    void insertTableCell(int type);
    //移除单元格
    void removeTableCell(int type);
private:
    QTableWidget * m_tablewidget = nullptr;
    //一行数据长度
    int m_RowDataLength;
    //水平表头
    QStringList m_hlist;
    //垂直表头
    QStringList m_vlist;

    QTableWidgetItem * m_currentitem;

    QMenu * m_menu;
    QAction * action;
};

#endif // WIDGET_H
