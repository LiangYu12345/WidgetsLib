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
    m_tablewidget = new QTableWidget(6,4,this);
    Init();
}

TableWidget::~TableWidget()
{
    delete m_tablewidget;
}

void TableWidget::appendHorizontalHeader(QString name)
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

void TableWidget::insertHorizontalHeader(int number, WidgetType type, QString name)
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

void TableWidget::removeHorizontalHeader(int number)
{
    m_tablewidget->removeColumn(number);   //包含释放其内存
}

void TableWidget::editHorizontalHeaderName(int column,QString &name)
{
    m_tablewidget->horizontalHeaderItem(column)->setText(name);
}

void TableWidget::appendVerticalHeader(QString name)
{
    auto number = m_tablewidget->verticalHeader()->count();
    m_tablewidget->insertRow(number);
    QTableWidgetItem *item = new QTableWidgetItem(name,QTableWidgetItem::Type);

    m_tablewidget->setVerticalHeaderItem(number,item);

    for(int nIndex = 0; nIndex < m_tablewidget->columnCount(); nIndex ++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        m_tablewidget->setItem(number,nIndex,item);
    }
    m_vlist.append(name);
}

void TableWidget::insertVerticalHeader(int number, WidgetType type, QString name)
{
    m_tablewidget->insertRow(number);
    QTableWidgetItem *item = new QTableWidgetItem(name,QTableWidgetItem::Type);

    m_tablewidget->setVerticalHeaderItem(number,item);

    for(int nIndex = 0; nIndex < m_tablewidget->columnCount(); nIndex ++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter);
        m_tablewidget->setItem(number,nIndex,item);
    }
    m_vlist.insert(number,name);
}

void TableWidget::removeVerticalHeader(int number)
{
    m_vlist.removeAt(number);
}

void TableWidget::editVerticalHeaderName(int row, QString &name)
{
    m_tablewidget->verticalHeaderItem(row)->setText(name);
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
    disconnect(m_tablewidget,&QTableWidget::cellChanged,this,&TableWidget::onEditPoint);
    if(m_tablewidget->item(row,column) == nullptr)
    {
        qDebug()<< u8"error cell text changed";
        return;
    }
    if(value == m_tablewidget->item(row,column)->text())
        return;
    m_tablewidget->item(row,column)->setText(value);
}

void TableWidget::onEditPoint(int row, int column)
{
//    qDebug()<<"Edited";
    auto value = m_tablewidget->item(row,column)->text();
    emit changed(row,column,value);
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
    m_vlist.append(QString::number(m_tablewidget->rowCount()));
    emit append(row);
    updateGeometry();
    Refresh();
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
    m_vlist.append(QString::number(num));
    emit append(num);
    updateGeometry();
    Refresh();
}

void TableWidget::removePoint(int num)
{
    m_tablewidget->removeRow(num);
    m_vlist.removeAt(num);
    emit removed(num);
    updateGeometry();
    Refresh();
}

void TableWidget::clearAll()
{
    m_tablewidget->clearContents();
    emit clear();
}

QSize TableWidget::sizeHint() const
{
    return QSize(m_hlist.size() * m_width, m_vlist.size() * m_height + m_height);
}

void TableWidget::deleteBtnClicked()
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

void TableWidget::lineEditTextChanged(QString text)
{
    qDebug()<<text;
}

void TableWidget::currentPointChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
//    qDebug()<<"currentChange";
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
    m_tablewidget->resize(this->size());
}

void TableWidget::Init()
{
    m_width = 52;
    m_height = 25;

    m_tablewidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //表头拓展
    m_tablewidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //表头拓展
    m_tablewidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    m_tablewidget->verticalHeader()->setVisible(false);
    //m_tablewidget->horizontalHeader()->setSectionsMovable(true);

    for(int Index = 0; Index < m_tablewidget->columnCount(); Index ++)
    {
        for(int nIndex = 0; nIndex < m_tablewidget->rowCount(); nIndex ++){
            m_tablewidget->setItem(nIndex,Index,new QTableWidgetItem());
            m_tablewidget->setRowHeight(nIndex, m_height);
            m_tablewidget->setColumnWidth(Index, m_width);
            m_tablewidget->item(nIndex, Index)->setTextAlignment(Qt::AlignCenter);
        }

    }
//    connect(m_tablewidget,&QTableWidget::cellActivated,this,[](){qDebug()<<"cellActived";});
//    connect(m_tablewidget,&QTableWidget::cellClicked,this,[](){qDebug()<<"cellClicked";});
//    connect(m_tablewidget,&QTableWidget::cellEntered,this,[](){qDebug()<<"cellEnterd";});
//    connect(m_tablewidget,&QTableWidget::cellPressed,this,[](){qDebug()<<"cellPressed";});

//    connect(m_tablewidget,&QTableWidget::itemActivated,this,[](){qDebug()<<"itemActivated";});
//    connect(m_tablewidget,&QTableWidget::itemChanged,this,[](){qDebug()<<"itemChanged";});
//    connect(m_tablewidget,&QTableWidget::itemDoubleClicked,this,[](){qDebug()<<"itemDoubleClicked";});
//    connect(m_tablewidget,&QTableWidget::itemEntered,this,[](){qDebug()<<"itemEntered";});
//    connect(m_tablewidget,&QTableWidget::itemPressed,this,[](){qDebug()<<"itemPressed";});
    connect(m_tablewidget,&QTableWidget::itemSelectionChanged,this,[=](){
        connect(m_tablewidget,&QTableWidget::cellChanged,this,&TableWidget::onEditPoint);
    });

    // 当前选项Cell 改变
    connect(m_tablewidget,&QTableWidget::currentItemChanged,this,&TableWidget::currentPointChanged);
    // 双击Cell
//    connect(m_tablewidget,&QTableWidget::cellDoubleClicked,this,&TableWidget::cellWidgetDoubleClicked);

    //m_tablewidget->setShowGrid(false);
    m_tablewidget->setAlternatingRowColors(true);
}

void TableWidget::Refresh()
{
    for(int nIndex = 0; nIndex < m_tablewidget->rowCount(); nIndex ++){
        m_tablewidget->item(nIndex, 0)->setText(QString::number(nIndex));
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
