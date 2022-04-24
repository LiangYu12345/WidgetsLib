#ifndef EXECLTABLEWIDGET_H
#define EXECLTABLEWIDGET_H

#include "tablewidget.h"

class WIDGETSLIB_EXPORT ExeclTableWidget : public TableWidget
{
public:
    ExeclTableWidget(QWidget * parent = nullptr);
    ExeclTableWidget(int row,int column,QWidget * parent = nullptr);
private:
    //表格操作
    //插入单元格
    void insertTableCell(int type);
    //移除单元格
    void removeTableCell(int type);
private:

    QMenu * m_menu;
    QAction * action;
};

#endif // EXECLTABLEWIDGET_H
