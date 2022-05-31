#include "waypointtablewidget.h"
#include <QDebug>
WaypointTableWidget::WaypointTableWidget(QWidget * parent)
    :TableWidget(parent)
{
    Init();
}

WaypointTableWidget::WaypointTableWidget(int row, int column, QWidget *parent)
{
    m_tablewidget->setRowCount(row);
    m_tablewidget->setColumnCount(column);

    Init();
}

QSize WaypointTableWidget::sizeHint() const
{
    return QSize(m_hlist.size() * m_width, m_vlist.size() * m_height + m_height);
}

void WaypointTableWidget::Init()
{
    m_hlist << u8"编号" << u8"经度(°)" << u8"纬度(°)" << u8"高度(m)" << u8"速度(m/s)";
    auto count = m_tablewidget->rowCount();
    for(int nIndex = 0; nIndex < count; ++nIndex){
        m_vlist << QString::number(nIndex + 1);
    }
    m_tablewidget->setHorizontalHeaderLabels(m_hlist);
    m_tablewidget->setVerticalHeaderLabels(m_vlist);

    m_tablewidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_tablewidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

