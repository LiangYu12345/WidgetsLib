#include "tablewidget.h"
#include <QDebug>
#include <QApplication>
TableWidget::TableWidget(int row, int column, QWidget *parent)
    :QWidget (parent)
{
    m_tablewidget = new QTableWidget(row,column,this);
    Init();
}

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
    m_tablewidget = new QTableWidget(5,4,this);
    Init();
}

TableWidget::~TableWidget()
{
    delete m_tablewidget;
}

void TableWidget::appendHeader(QString name)
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

void TableWidget::insertHeader(int number, WidgetType type, QString name)
{
    m_tablewidget->insertColumn(number);
    QTableWidgetItem *item = new QTableWidgetItem(name,QTableWidgetItem::Type);
    m_tablewidget->setHorizontalHeaderItem(number,item);
    switch (type) {
        case Text:
        for(int nIndex = 0; nIndex < m_tablewidget->rowCount(); nIndex ++)
        {
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            m_tablewidget->setItem(nIndex,number,item);
        }
        break;
        case Button:
        for(int nIndex = 0; nIndex < m_tablewidget->rowCount(); nIndex ++)
        {
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            m_tablewidget->setItem(nIndex,number,item);

            m_tablewidget->setCellWidget(nIndex,number,CreateBtnWdiget(u8"删除"));
        }
        break;
        case LineEdit:
        for(int nIndex = 0; nIndex < m_tablewidget->rowCount(); nIndex ++)
        {
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            m_tablewidget->setItem(nIndex,number,item);

            m_tablewidget->setCellWidget(0,3,CreateLineEditWdiget());
        }
        break;
        case Icon:
        for(int nIndex = 0; nIndex < m_tablewidget->rowCount(); nIndex ++)
        {
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            m_tablewidget->setItem(nIndex,number,item);

            m_tablewidget->setCellWidget(0,3,CreateIconWdiget(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon).pixmap(40,40)));
        }
        break;
        default:
        break;
    }

}

void TableWidget::removeHeader(int number)
{
    m_tablewidget->removeColumn(number);   //包含释放其内存
}

void TableWidget::edihorizontalHeaderName(int column,QString &name)
{
    m_tablewidget->horizontalHeaderItem(column)->setText(name);
}


QList<QTableWidgetItem *> TableWidget::m_points() const
{
    QList<QTableWidgetItem *> points;

    for(int Index = 0; Index < m_tablewidget->rowCount(); Index ++)
    {
        for(int nIndex = 0; nIndex < m_tablewidget->columnCount(); nIndex ++)
        {
            points.append(m_tablewidget->item(Index,nIndex));
        }
    }
    return points;
}

int TableWidget::getRowCount() const
{
    return m_tablewidget->rowCount();
}

int TableWidget::getColumnCount() const
{
    return m_tablewidget->columnCount();
}

void TableWidget::editPoint(int row, int column, QString value)
{
    if(m_tablewidget->item(row,column) == nullptr)
    {
        qDebug()<< u8"错误修改";
        return;
    }
    m_tablewidget->item(row,column)->setText(value);
}

void TableWidget::appendPoint()
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

void TableWidget::insertPoint(int num)
{
    m_tablewidget->insertRow(num);

    for(int nIndex = 0; nIndex < m_tablewidget->columnCount(); nIndex ++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        m_tablewidget->setItem(num,nIndex,item);
    }
}

void TableWidget::removePoint(int num)
{
    m_tablewidget->removeRow(num);
}

void TableWidget::editverticalHeaderName(int row, QString &name)
{
    m_tablewidget->verticalHeaderItem(row)->setText(name);
}

void TableWidget::clearAll()
{
    m_tablewidget->clearContents();
}

QSize TableWidget::sizeHint() const
{
    return QSize(200, 200);
}

void TableWidget::slotBtnClicked()
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

void TableWidget::slotLineEditTextChanged(QString text)
{
    qDebug()<<text;
}

void TableWidget::slotChooseCurrentPointChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    Q_UNUSED(previous);
    if(m_currentitem == current)
        return;
    m_currentitem = current;
}

void TableWidget::slotCellWidgetDoubleClicked(int row, int column)
{
    ;
}

void TableWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    m_tablewidget->resize(this->size());
}

void TableWidget::Init()
{
    connect(m_tablewidget,&QTableWidget::currentItemChanged,this,&TableWidget::slotChooseCurrentPointChanged);

    m_tablewidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //表头拓展
    m_tablewidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //表头拓展
    m_tablewidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    m_tablewidget->verticalHeader()->setVisible(false);
    //m_tablewidget->horizontalHeader()->setSectionsMovable(true);

    for(int Index = 0; Index < m_tablewidget->columnCount(); Index ++)
    {
        for(int nIndex = 0; nIndex < m_tablewidget->rowCount(); nIndex ++)
            m_tablewidget->setItem(nIndex,Index,new QTableWidgetItem());
    }

    connect(m_tablewidget,&QTableWidget::cellDoubleClicked,this,&TableWidget::slotCellWidgetDoubleClicked);

    Refresh();
}

void TableWidget::Refresh()
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

QWidget *TableWidget::CreateBtnWdiget(const QString &btnname)
{
    QWidget * item = new QWidget;

    QPushButton * btn = new QPushButton(btnname);
    btn->setCheckable(true);

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(btn);

    item->setLayout(layout);
    connect(btn,&QPushButton::clicked,this,&TableWidget::slotBtnClicked);
    return item;
}

QWidget *TableWidget::CreateLineEditWdiget()
{
    QWidget * item = new QWidget;

    QLineEdit * lineEdit = new QLineEdit;

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(lineEdit);

    item->setLayout(layout);
    connect(lineEdit,&QLineEdit::textChanged,this,&TableWidget::slotLineEditTextChanged);
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
