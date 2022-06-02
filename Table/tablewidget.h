#ifndef WIDGET_H
#define WIDGET_H

#include "widgetslib_global.h"
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

class WIDGETSLIB_EXPORT TableWidget : public QWidget
{
    Q_OBJECT

public:
    TableWidget(int row,int column,QWidget *parent = nullptr);
    TableWidget(QWidget *parent = nullptr);
    ~TableWidget() override;
    //添加一列水平表头
    void appendHorizontalHeader(QString name);
    //插入一列水平表头
    void insertHorizontalHeader(int number,WidgetType type = Text,QString name = QString(u8""));
    //移除一列水平表头
    void removeHorizontalHeader(int number);
    //修改水平表头名称
    void editHorizontalHeaderName(int column,QString &name);
    //添加一列水平表头
    void appendVerticalHeader(QString name);
    //插入一列水平表头
    void insertVerticalHeader(int number,WidgetType type = Text,QString name = QString(u8""));
    //移除一列水平表头
    void removeVerticalHeader(int number);
    //修改垂直表头名称
    void editVerticalHeaderName(int row,QString &name);
    //获取当前行的数据
    QList<QTableWidgetItem *> m_points() const;
    //获取表格总行数
    int getRowCount() const;
    int getColumnCount() const;
    int getRowHeight() const;
    int getColumnWidth() const;
    //编辑表格中一个Point的单个数据   / noet: 差一个编辑表格中一个点的单个数据的数据类型：Icon，Btn
    void editPoint(int row,int column,QString value);
    //编辑表格中一个Point的单个数据
    void onEditPoint(int row,int column);
    //添加一行  默认为空
    void appendPoint();
    //插入至某行
    void insertPoint(int num);
    //移除某行
    void removePoint(int num);
    //清除所有数据
    void clearAll();

    virtual QSize sizeHint() const override;
private slots:
    void deleteBtnClicked();
    void lineEditTextChanged(QString text);
    void currentPointChanged(QTableWidgetItem *current, QTableWidgetItem *previous);
    void cellWidgetDoubleClicked(int row,int column);
signals:
    // 添加表头
    void headAppend(int row);
    // 插入表头
    void headInsert(int row);
    // 删除表头
    void headRemove(int row);
    // 编辑表头
    void headEdit(int row);
    // 添加
    void append(int row);
    // 插入点
    void insert();
    // 删除
    void removed(int row);
    // 表格改变
    void changed(int row,int column,QString str);
    // 清空
    void clear();
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
protected:
    QTableWidget * m_tablewidget = nullptr;
    QTableWidgetItem * m_currentItem;

    //水平表头
    QStringList m_hlist;
    //垂直表头
    QStringList m_vlist;

    // 格宽
    int m_width;
    // 格高
    int m_height;
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
};

#endif // WIDGET_H
