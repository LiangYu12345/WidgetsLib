#include "waypointtablewidget.h"
#include <QDebug>
WaypointTableWidget::WaypointTableWidget(QWidget * parent)
    :TableWidget(parent)
{
    Init();
}

WaypointTableWidget::WaypointTableWidget(int row, int column, QWidget *parent)
{
    m_tableWidget->setRowCount(row);
    m_tableWidget->setColumnCount(column);

    Init();
}

QSize WaypointTableWidget::sizeHint() const
{
    return QSize(m_hlist.size() * m_width, m_tableWidget->verticalHeader()->count() * m_height + m_height);
}

void WaypointTableWidget::Init()
{
    m_hlist << u8"编号" << u8"经度(°)" << u8"纬度(°)" << u8"高度(m)" << u8"速度(m/s)";
    m_tableWidget->setHorizontalHeaderLabels(m_hlist);

    m_tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

