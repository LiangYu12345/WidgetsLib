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
    auto count = m_tablewidget->rowCount();
    for(int nIndex = 0; nIndex < count; ++nIndex){
        m_vlist << QString::number(nIndex + 1);
    }
    m_tablewidget->setHorizontalHeaderLabels(m_hlist);
    m_tablewidget->setVerticalHeaderLabels(m_vlist);

    //设置滑动区域为无
    m_tablewidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_tablewidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
