#include "waypointtablewidget.h"

WaypointTableWidget::WaypointTableWidget(QWidget * parent)
    :TableWidget(parent)
{

}

WaypointTableWidget::WaypointTableWidget(int row, int column, QWidget *parent)
{
    m_tablewidget->setRowCount(row);
    m_tablewidget->setColumnCount(column);
}

