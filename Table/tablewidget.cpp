#include "tablewidget.h"
#include <QDebug>
#include <QApplication>
TableWidget::TableWidget(int row, int column, QWidget *parent)
    :QWidget (parent)
{
    m_tableWidget = new QTableWidget(row, column, this);
    Init();
}

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
    m_tableWidget = new QTableWidget(6, 4, this);
    Init();
}

TableWidget::~TableWidget()
{
    delete m_tableWidget;
}

void TableWidget::appendHorizontalHeader(QString name)
{
    auto number = m_tableWidget->horizontalHeader()->count();
    m_tableWidget->insertColumn(number);
    QTableWidgetItem *item = new QTableWidgetItem(name, QTableWidgetItem::Type);
    m_tableWidget->setHorizontalHeaderItem(number, item);

    for(int nIndex = 0; nIndex < m_tableWidget->rowCount(); nIndex ++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(nIndex, number, item);
    }
}

void TableWidget::insertHorizontalHeader(int number, WidgetType type, QString name)
{
    m_tableWidget->insertColumn(number);
    QTableWidgetItem *item = new QTableWidgetItem(name, QTableWidgetItem::Type);
    m_tableWidget->setHorizontalHeaderItem(number, item);
    switch (type) {
        case Text:
        for(int nIndex = 0; nIndex < m_tableWidget->rowCount(); nIndex ++)
        {
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            m_tableWidget->setItem(nIndex, number, item);
        }
        break;
        case Button:
        for(int nIndex = 0; nIndex < m_tableWidget->rowCount(); nIndex ++)
        {
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            m_tableWidget->setItem(nIndex, number, item);

            m_tableWidget->setCellWidget(nIndex, number, CreateBtnWdiget(u8"删除"));
        }
        break;
        case LineEdit:
        for(int nIndex = 0; nIndex < m_tableWidget->rowCount(); nIndex ++)
        {
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            m_tableWidget->setItem(nIndex, number, item);

            m_tableWidget->setCellWidget(nIndex, number, CreateLineEditWdiget());
        }
        break;
        case Icon:
        for(int nIndex = 0; nIndex < m_tableWidget->rowCount(); nIndex ++)
        {
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            m_tableWidget->setItem(nIndex, number, item);

            m_tableWidget->setCellWidget(nIndex, number, CreateIconWdiget(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon).pixmap(40,40)));
        }
        break;
        default:
        break;
    }
}

void TableWidget::removeHorizontalHeader(int number)
{
    m_tableWidget->takeHorizontalHeaderItem(number);
}

void TableWidget::editHorizontalHeaderName(int column,QString &name)
{
    m_tableWidget->horizontalHeaderItem(column)->setText(name);
}

void TableWidget::appendVerticalHeader(QString name)
{
    auto number = m_tableWidget->verticalHeader()->count();
    m_tableWidget->insertRow(number);
    QTableWidgetItem *item = new QTableWidgetItem(name,QTableWidgetItem::Type);
    m_tableWidget->setVerticalHeaderItem(number,item);

    for(int nIndex = 0; nIndex < m_tableWidget->columnCount(); nIndex ++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(number,nIndex,item);
    }
}

void TableWidget::insertVerticalHeader(int number, WidgetType type, QString name)
{
    m_tableWidget->insertRow(number);
    QTableWidgetItem *item = new QTableWidgetItem(name,QTableWidgetItem::Type);
    m_tableWidget->setVerticalHeaderItem(number,item);

    for(int nIndex = 0; nIndex < m_tableWidget->columnCount(); nIndex ++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(number,nIndex,item);
    }
}

void TableWidget::removeVerticalHeader(int number)
{
    m_tableWidget->takeVerticalHeaderItem(number);
}

void TableWidget::editVerticalHeaderName(int row, QString &name)
{
    m_tableWidget->verticalHeaderItem(row)->setText(name);
}

QList<QTableWidgetItem *> TableWidget::m_points() const
{
    QList<QTableWidgetItem *> points;
    for(int Index = 0; Index < m_tableWidget->rowCount(); Index ++)
    {
        for(int nIndex = 0; nIndex < m_tableWidget->columnCount(); nIndex ++)
        {
            points.append(m_tableWidget->item(Index,nIndex));
        }
    }
    return points;
}

int TableWidget::getRowCount() const
{
    return m_tableWidget->rowCount();
}

int TableWidget::getColumnCount() const
{
    return m_tableWidget->columnCount();
}

int TableWidget::getRowHeight() const
{
    return m_height;
}

int TableWidget::getColumnWidth() const
{
    return m_width;
}

void TableWidget::editPoint(int row, int column, QString value)
{
    disconnect(m_tableWidget,&QTableWidget::cellChanged,this,&TableWidget::onEditPoint);
    if(m_tableWidget->item(row,column) == nullptr)
    {
        qDebug()<< u8"error cell text changed";
        return;
    }
    if(value == m_tableWidget->item(row,column)->text())
        return;
    m_tableWidget->item(row,column)->setText(value);
    //connect(m_tableWidget,&QTableWidget::cellChanged,this,&TableWidget::onEditPoint);
}

void TableWidget::onEditPoint(int row, int column)
{
    auto value = m_tableWidget->item(row,column)->text();
    emit changed(row,column,value);
}

void TableWidget::appendPoint()
{
    auto row = m_tableWidget->rowCount();
    m_tableWidget->insertRow(row);

    for(int nIndex = 0; nIndex < m_tableWidget->columnCount(); nIndex ++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(row,nIndex,item);
    }
    emit append();
    updateGeometry();
    Refresh();
}

void TableWidget::insertPoint(int num)
{
    m_tableWidget->insertRow(num);

    for(int nIndex = 0; nIndex < m_tableWidget->columnCount(); nIndex ++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        m_tableWidget->setItem(num,nIndex,item);
    }
    emit insert(num);
    updateGeometry();
    Refresh();
}

void TableWidget::removePoint(int num)
{
    m_tableWidget->removeRow(num);
    emit removed(num);
    updateGeometry();
    Refresh();
}

void TableWidget::clearAll()
{
    m_tableWidget->clearContents();
    auto rowCount = m_tableWidget->rowCount();
    for(auto nIndex = rowCount - 1; nIndex >= 0; --nIndex){
        m_tableWidget->removeRow(nIndex);
    }
    updateGeometry();
    emit clear();
}

QSize TableWidget::sizeHint() const
{
    return QSize(m_hlist.size() * m_width, m_tableWidget->rowCount() * m_height + m_height);
}

void TableWidget::deleteBtnClicked()
{
    auto btn = reinterpret_cast<QPushButton *>(sender());
    auto widget = btn->parent();
    for(int nIndex = 0; nIndex < m_tableWidget->columnCount(); ++nIndex){
        for(int Index = 0; Index < m_tableWidget->rowCount(); ++Index)
        {
            if(widget == m_tableWidget->cellWidget(nIndex, Index))
                m_tableWidget->removeRow(nIndex);
        }
    }
}

void TableWidget::lineEditTextChanged(QString text)
{
//    qDebug()<<text;
}

void TableWidget::currentPointChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    Q_UNUSED(previous);
    if(m_currentItem == current)
        return;
    m_currentItem = current;
}

void TableWidget::cellWidgetDoubleClicked(int row, int column)
{
//    qDebug()<<"doubleClicked";
}

void TableWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    m_tableWidget->resize(sizeHint());
}

void TableWidget::Init()
{
    m_width = 52;
    m_height = 26;

    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //表头拓展
    m_tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //表头拓展
    m_tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    m_tableWidget->verticalHeader()->setVisible(false);

    for(int Index = 0; Index < m_tableWidget->columnCount(); Index ++)
    {
        for(int nIndex = 0; nIndex < m_tableWidget->rowCount(); nIndex ++){
            m_tableWidget->setItem(nIndex,Index,new QTableWidgetItem());
            m_tableWidget->setRowHeight(nIndex, m_height);
            m_tableWidget->setColumnWidth(Index, m_width);
            m_tableWidget->item(nIndex, Index)->setTextAlignment(Qt::AlignCenter);
        }
    }

    // 选择范围改变
//    connect(m_tableWidget,&QTableWidget::itemSelectionChanged,this,&TableWidget::onSelecteRangChanged);
//    // Cell 值改变
//    connect(m_tableWidget,&QTableWidget::cellChanged,this,&TableWidget::onEditPoint);
    connect(m_tableWidget,&QTableWidget::itemSelectionChanged,this,[=](){
        connect(m_tableWidget,&QTableWidget::cellChanged,this,&TableWidget::onEditPoint);
    });
    // 当前选项Cell 改变
    connect(m_tableWidget,&QTableWidget::currentItemChanged,this,&TableWidget::currentPointChanged);
    // 双击Cell
    connect(m_tableWidget,&QTableWidget::cellDoubleClicked,this,&TableWidget::cellWidgetDoubleClicked);

//    m_tableWidget->setShowGrid(false);
    m_tableWidget->setAlternatingRowColors(true);

//    m_menu = new QMenu(this);
//    QAction *del = new QAction(u8"删除航点");
//    m_menu->addAction(del);
//    connect(del, &QAction::triggered, this, &TableWidget::onDeleteWayPoint);

//    m_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(m_tableWidget, &QTableWidget::customContextMenuRequested, this, &TableWidget::onMenu);
}

void TableWidget::Refresh()
{
    for(int nIndex = 0; nIndex < m_tableWidget->rowCount(); nIndex ++){
        m_tableWidget->item(nIndex, 0)->setText(QString::number(nIndex));
    }
}

QWidget *TableWidget::CreateBtnWdiget(const QString &btnname)
{
    QWidget * item = new QWidget;

    QPushButton * btn = new QPushButton(btnname);
    btn->setCheckable(true);

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(btn);

    item->setLayout(layout);
    connect(btn,&QPushButton::clicked,this,&TableWidget::deleteBtnClicked);
    return item;
}

QWidget *TableWidget::CreateLineEditWdiget()
{
    QWidget * item = new QWidget;

    QLineEdit * lineEdit = new QLineEdit;

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(lineEdit);

    item->setLayout(layout);
    connect(lineEdit,&QLineEdit::textChanged,this,&TableWidget::lineEditTextChanged);
    return item;
}

QWidget *TableWidget::CreateIconWdiget(const QPixmap &pixmap)
{
    QWidget * item = new QWidget;

    QLabel * lable = new QLabel;
    lable->setPixmap(pixmap);
    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(lable);

    item->setLayout(layout);

    return item;
}

void TableWidget::onSelecteRangChanged()
{
    m_tableSelecteRows.clear();
    auto lists = m_tableWidget->selectedItems();
    for(auto nIndex = 0; nIndex < lists.count(); ++nIndex){
        int Row = lists.at(nIndex)->row();

        if(m_tableSelecteRows.contains(Row))
                continue;
        m_tableSelecteRows.insert(Row, Row);
    }
}

void TableWidget::onDeleteWayPoint()
{
    disconnect(m_tableWidget, &QTableWidget::itemSelectionChanged, this, &TableWidget::onSelecteRangChanged);
    auto count = m_tableWidget->verticalHeader()->count();

    /// 表格反向遍历容器删除航点
    for(auto iter =  --m_tableSelecteRows.end(); iter != --m_tableSelecteRows.begin(); --iter){
        if(iter.value() > count)
            return;
        m_tableWidget->removeRow(iter.value());
    }

    /// 删除后重置表格航点
    Refresh();

    connect(m_tableWidget, &QTableWidget::itemSelectionChanged, this, &TableWidget::onSelecteRangChanged);
}

void TableWidget::onMenu(const QPoint &pos)
{
    Q_UNUSED(pos);
    m_menu->move(cursor().pos());
    m_menu->exec();
}
