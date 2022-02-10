#include "tablewidget.h"
#include <QDebug>
#include <QApplication>
PointsWidget::PointsWidget(int row, int column, QWidget *parent)
    :QWidget (parent)
{
    m_tablewidget = new QTableWidget(row,column,this);
    Init();
}

PointsWidget::PointsWidget(QWidget *parent)
    : QWidget(parent)
{
    m_tablewidget = new QTableWidget(5,4,this);
    Init();
}

PointsWidget::~PointsWidget()
{
    delete m_tablewidget;
}

void PointsWidget::appendHeader(QString name)
{
    auto number = m_tablewidget->horizontalHeader()->count();
    m_tablewidget->insertColumn(number);
    QTableWidgetItem *item = new QTableWidgetItem(name,QTableWidgetItem::Type);

    m_tablewidget->setHorizontalHeaderItem(number,item);

    for(int nIndex = 0; nIndex < m_tablewidget->rowCount(); nIndex ++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        m_tablewidget->setItem(nIndex,number,item);
    }
}

void PointsWidget::insertHeader(int number, WidgetType type, QString name)
{
    m_tablewidget->insertColumn(number);
    QTableWidgetItem *item = new QTableWidgetItem(name,QTableWidgetItem::Type);
    m_tablewidget->setHorizontalHeaderItem(number,item);

    for(int nIndex = 0; nIndex < m_tablewidget->rowCount(); nIndex ++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        m_tablewidget->setItem(nIndex,number,item);
    }
}

void PointsWidget::removeHeader(int number)
{
    m_tablewidget->removeColumn(number);   //包含释放其内存
}

QList<QTableWidgetItem *> PointsWidget::m_points() const
{
    return QList<QTableWidgetItem *>();
}

int PointsWidget::getRowCount() const
{
    return m_tablewidget->rowCount();
}

void PointsWidget::editPoint(int row, int column, QString value)
{
    if(m_tablewidget->item(row,column) == nullptr)
    {
        qDebug()<< u8"错误修改";
        return;
    }
    m_tablewidget->item(row,column)->setText(value);
}

void PointsWidget::appendPoint()
{
    auto row = m_tablewidget->rowCount();
    m_tablewidget->insertRow(row);

    for(int nIndex = 0; nIndex < m_tablewidget->columnCount(); nIndex ++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        m_tablewidget->setItem(row,nIndex,item);
    }
}

void PointsWidget::insertPoint(int num)
{
    m_tablewidget->insertRow(num);

    for(int nIndex = 0; nIndex < m_tablewidget->columnCount(); nIndex ++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        m_tablewidget->setItem(num,nIndex,item);
    }
}

void PointsWidget::removePoint(int num)
{
    m_tablewidget->removeRow(num);
}

void PointsWidget::clearAll()
{
    m_tablewidget->clearContents();
}

void PointsWidget::slotBtnClicked()
{
    auto btn = reinterpret_cast<QPushButton *>(sender());
    auto widget =btn->parent();
    for(int nIndex = 0; nIndex < m_tablewidget->horizontalHeader()->count(); nIndex ++)
        for(int Index = 0; Index < m_tablewidget->verticalHeader()->count(); Index ++)
        {
            if(widget == m_tablewidget->cellWidget(nIndex,Index))
                m_tablewidget->removeRow(nIndex);
        }

}

void PointsWidget::slotLineEditTextChanged(QString text)
{
    qDebug()<<text;
}

void PointsWidget::slotChooseCurrentPointChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    Q_UNUSED(previous);
    if(m_currentitem == current)
        return;
    m_currentitem = current;
}

void PointsWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if(this->size().width() > 500 || this->size().height() > 400)
        m_tablewidget->resize(this->size());
}

void PointsWidget::Init()
{
    //初始化 表格 ： 编号 经度  纬度  高度
    m_tablewidget->resize(500,400);

    m_hlist << u8"编号" << u8"经度(°)" << u8"纬度(°)" << u8"高度(m)";
    m_vlist << u8"1" << u8"2" << u8"3" << u8"4" << u8"5";
    m_tablewidget->setHorizontalHeaderLabels(m_hlist);
    m_tablewidget->setVerticalHeaderLabels(m_vlist);

    connect(m_tablewidget,&QTableWidget::currentItemChanged,this,&PointsWidget::slotChooseCurrentPointChanged);

    m_tablewidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //表头拓展
    m_tablewidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //表头拓展
    m_tablewidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    m_tablewidget->verticalHeader()->setVisible(false);
    //m_tablewidget->horizontalHeader()->setSectionsMovable(true);

    for(int Index = 0; Index < m_tablewidget->columnCount(); Index ++)
    {
        for(int nIndex = 0; nIndex < m_tablewidget->rowCount(); nIndex ++)
            m_tablewidget->setItem(nIndex,Index,new QTableWidgetItem(QString::number(nIndex+1)));
    }

    QString str(u8"删除");
    m_tablewidget->setCellWidget(0,3,CreateBtnWdiget(str));
    m_tablewidget->setCellWidget(1,3,CreateLineEditWdiget());
    m_tablewidget->setCellWidget(2,3,CreateIconWdiget(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon).pixmap(40,40)));

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

    Refresh();
}

void PointsWidget::Refresh()
{

    auto column = m_tablewidget->columnCount();
    auto row = m_tablewidget->rowCount();

    for(int Index = 0; Index < column; Index ++)
    {
        for(int nIndex = 0; nIndex < row; nIndex ++)
        {
            m_tablewidget->item(nIndex,Index)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

QWidget *PointsWidget::CreateBtnWdiget(const QString &btnname)
{
    QWidget * item = new QWidget;

    QPushButton * btn = new QPushButton(btnname);
    btn->setCheckable(true);

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(btn);

    item->setLayout(layout);
    connect(btn,&QPushButton::clicked,this,&PointsWidget::slotBtnClicked);
    return item;
}

QWidget *PointsWidget::CreateLineEditWdiget()
{
    QWidget * item = new QWidget;

    QLineEdit * lineEdit = new QLineEdit;

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(lineEdit);

    item->setLayout(layout);
    connect(lineEdit,&QLineEdit::textChanged,this,&PointsWidget::slotLineEditTextChanged);
    return item;
}

QWidget *PointsWidget::CreateIconWdiget(const QPixmap &pixmap)
{
    QWidget * item = new QWidget;

    QLabel * lable = new QLabel;
    lable->setPixmap(pixmap);
    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(lable);

    item->setLayout(layout);

    return item;
}

void PointsWidget::insertTableCell(int type)
{
    switch (type) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        insertPoint(m_tablewidget->row(m_currentitem));
        break;
    case 4:
        insertHeader(m_tablewidget->column(m_currentitem),WidgetType::Text,"");
        break;
    default:
        ;
    }
}

void PointsWidget::removeTableCell(int type)
{
    switch (type) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        removePoint(m_tablewidget->row(m_currentitem));
        break;
    case 4:
        removeHeader(m_tablewidget->column(m_currentitem));
        break;
    default:
        ;
    }
}
