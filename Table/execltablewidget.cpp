#include "execltablewidget.h"

ExeclTableWidget::ExeclTableWidget(QWidget * parent)
    :TableWidget(parent)
{

    //菜单栏
    {
    m_tablewidget->setContextMenuPolicy(Qt::CustomContextMenu);
    m_menu = new QMenu(m_tablewidget);

    QMenu * insertmenu = new QMenu(u8"插入", this);

//    action = new QAction(u8"单元格右移", this);
//    connect(action, &QAction::triggered, this, [=](){insertTableCell(1);});
//    insertmenu->addAction(action);
//    action = new QAction(u8"单元格下移", this);
//    connect(action, &QAction::triggered, this, [=](){insertTableCell(2);});
//    insertmenu->addAction(action);
    action = new QAction(u8"整行", this);
    connect(action, &QAction::triggered, this, [=](){insertTableCell(3);});
    insertmenu->addAction(action);
    action = new QAction(u8"整列", this);
    connect(action, &QAction::triggered, this, [=](){insertTableCell(4);});
    insertmenu->addAction(action);
    m_menu->addMenu(insertmenu);

    QMenu * removemenu = new QMenu(u8"删除",this);
//    action = new QAction(u8"单元格左移", this);
//    connect(action, &QAction::triggered, this, [=](){removeTableCell(1);});
//    removemenu->addAction(action);
//    action = new QAction(u8"单元格上移", this);
//    connect(action, &QAction::triggered, this, [=](){removeTableCell(2);});
//    removemenu->addAction(action);
    action = new QAction(u8"整行", this);
    connect(action, &QAction::triggered, this, [=](){removeTableCell(3);});
    removemenu->addAction(action);
    action = new QAction(u8"整列", this);
    connect(action, &QAction::triggered, this, [=](){removeTableCell(4);});
    removemenu->addAction(action);
    m_menu->addMenu(removemenu);

    connect(m_tablewidget,&QWidget::customContextMenuRequested,this,[=](){m_menu->exec(QCursor::pos());});
    }
}

ExeclTableWidget::ExeclTableWidget(int row, int column, QWidget *parent)
{
    m_tablewidget->setRowCount(row);
    m_tablewidget->setColumnCount(column);
}

void ExeclTableWidget::insertTableCell(int type)
{
    switch (type) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        insertPoint(m_tablewidget->row(m_currentItem));
        break;
    case 4:
        insertHorizontalHeader(m_tablewidget->column(m_currentItem),WidgetType::Text,"");
        break;
    default:
        ;
    }
}

void ExeclTableWidget::removeTableCell(int type)
{
    switch (type) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        removePoint(m_tablewidget->row(m_currentItem));
        break;
    case 4:
        removeHorizontalHeader(m_tablewidget->column(m_currentItem));
        break;
    default:
        ;
    }
}

