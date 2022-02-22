#include "polygontablewidget.h"

PolygonTableWidget::PolygonTableWidget(QWidget * parent)
    :TableWidget(parent)
{
    Init();
}

PolygonTableWidget::PolygonTableWidget(int row, int column, QWidget *parent)
    :TableWidget(parent)
{
    m_tablewidget->setColumnCount(column);
    m_tablewidget->setRowCount(row);

    Init();
}

void PolygonTableWidget::Init()
{
    //初始化 表格 ： 编号 经度  纬度  高度
    m_hlist << u8"编号" << u8"经度(°)" << u8"纬度(°)" << u8"高度(m)";
    m_vlist << u8"1" << u8"2" << u8"3" << u8"4" << u8"5"<<u8"6";
    m_tablewidget->setHorizontalHeaderLabels(m_hlist);
    m_tablewidget->setVerticalHeaderLabels(m_vlist);

    //设置滑动区域为无
}
