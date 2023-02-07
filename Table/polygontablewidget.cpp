#include "polygontablewidget.h"

PolygonTableWidget::PolygonTableWidget(QWidget * parent)
    :TableWidget(parent)
{
    Init();
}

PolygonTableWidget::PolygonTableWidget(int row, int column, QWidget *parent)
    :TableWidget(parent)
{
    m_tableWidget->setColumnCount(column);
    m_tableWidget->setRowCount(row);

    Init();
}

void PolygonTableWidget::Init()
{
    //初始化 表格 ： 编号 经度  纬度  高度
    m_hlist << u8"编号" << u8"经度(°)" << u8"纬度(°)" << u8"高度(m)";
    m_tableWidget->setHorizontalHeaderLabels(m_hlist);

    //设置滑动区域为无
    m_tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
