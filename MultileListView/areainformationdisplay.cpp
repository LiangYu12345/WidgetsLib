#include "areainformationdisplay.h"
#include <QDebug>

AreaInformationDisplay::AreaInformationDisplay(QWidget *parent)
    : QWidget(parent)
{
    m_gLayout = new QGridLayout;

    this->setLayout(m_gLayout);

    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setAttribute(Qt::WA_TransparentForMouseEvents,true);

    ///  构建一个默认显示表单
    this->addItem(0,u8"编号",u8"0");
    this->addItem(1,u8"名称",u8"0");
    this->addItem(2,u8"经度(°)",u8"0");
    this->addItem(3,u8"纬度(°)",u8"0");
    this->addItem(4,u8"高度(Km)",u8"0");
    this->addItem(5,u8"方位",u8"0");
    this->addItem(6,u8"俯仰",u8"0");
    this->addItem(7,u8"滚转",u8"0");
    this->addItem(8,u8"速度(Km/s)",u8"0");

    qDebug()<<m_gLayout->count() << "total";
    for(int nIndex = 0; nIndex < m_gLayout->count(); ++ nIndex){
        qDebug()<<nIndex <<m_gLayout->itemAt(nIndex) <<"total";
    }
}

void AreaInformationDisplay::addItem(int Index, const QString &name, const QString &value)
{
    QLabel * key = new QLabel;
    QLabel * val = new QLabel;
    key->setText(name);
    val->setText(value);
    m_gLayout->addWidget(key,Index,0,1,1);
    m_gLayout->addWidget(val,Index,1,1,1);
}

void AreaInformationDisplay::appendItem(const QString &name, const QString &value)
{
    auto count = m_gLayout->rowCount();
    QLabel * key = new QLabel;
    QLabel * val = new QLabel;
    key->setText(name);
    val->setText(value);
    m_gLayout->addWidget(key,count,0,1,1);
    m_gLayout->addWidget(val,count,1,1,1);
}

void AreaInformationDisplay::removeItem(int Index)
{
    qDebug()<<m_gLayout->count()<<m_gLayout->rowCount()<<m_gLayout->itemAt(Index);
    ///  该移除网格布局中LayoutItem  需要移除他当前行的LayoutItem;
    ///  note: 删除从  (columnCount-1) *Index  到  columnCount * Index
    auto columnCount = m_gLayout->columnCount();
    auto begin = (columnCount-1)*Index;
    auto end = columnCount * Index;
    if(begin > end){
        qSwap(begin,end);
    }
    for(int nIndex = begin; nIndex < end; ++nIndex){
        auto item = m_gLayout->itemAt(nIndex);
        m_gLayout->removeItem(item);
    }
}

void AreaInformationDisplay::changeItem(int Index, const QString &name, const QString &value)
{
    auto layoutKeyItem = m_gLayout->itemAtPosition(Index,0);
    auto labelKey = static_cast<QLabel *>(layoutKeyItem->widget());
    labelKey->setText(name);
    auto layoutValItem = m_gLayout->itemAtPosition(Index,1);
    auto labelVal = static_cast<QLabel *>(layoutValItem->widget());
    labelVal->setText(value);
}

void AreaInformationDisplay::changeItemKey(int Index, const QString &name)
{
    qDebug()<<"changeItemKey";
    auto layoutKeyItem = m_gLayout->itemAtPosition(Index,0);
    auto labelKey = static_cast<QLabel *>(layoutKeyItem->widget());
    labelKey->setText(name);
    qDebug()<<"finishChangedItemKey";
}

void AreaInformationDisplay::changeItemVal(int Index, const QString &value)
{
    auto layoutValItem = m_gLayout->itemAtPosition(Index,1);
    auto labelVal = static_cast<QLabel *>(layoutValItem->widget());
    labelVal->setText(value);
}

void AreaInformationDisplay::chooseMode(const int &type)
{
    auto column = m_gLayout->columnCount();
    ///  现 飞机 圆形 矩形 显示参数为8 多边形显示参数不固定
    ///  note : 如果个数不统一  即为 动态添加和改变Key
    if(type == 1){
        //dealRowCount(9);
        this->changeItemKey(0 * column,u8"编号");
        this->changeItemKey(1 * column + 1,u8"名称");
        this->changeItemKey(2 * column + 1,u8"经度(°)");
        this->changeItemKey(3 * column + 1,u8"纬度(°)");
        this->changeItemKey(4 * column + 1,u8"高度(Km)");
        this->changeItemKey(5 * column + 1,u8"方位");
        this->changeItemKey(6 * column + 1,u8"俯仰");
        this->changeItemKey(7 * column + 1,u8"滚转");
        this->changeItemKey(8 * column + 1,u8"速度(Km/s)");
    }
    else if(type == 2){
        //dealRowCount(9);
        this->changeItemKey(0 * column,u8"编号");
        this->changeItemKey(1 * column + 1,u8"名称");
        this->changeItemKey(2 * column + 1,u8"经度(°)");
        this->changeItemKey(3 * column + 1,u8"纬度(°)");
        this->changeItemKey(4 * column + 1,u8"高度(Km)");
        this->changeItemKey(5 * column + 1,u8"方位");
        this->changeItemKey(6 * column + 1,u8"俯仰");
        this->changeItemKey(7 * column + 1,u8"滚转");
        this->changeItemKey(8 * column + 1,u8"速度(Km/s)");
    }
    else if(type == 3){
        //dealRowCount(9);
        this->changeItemKey(0 * column,u8"编号");
        this->changeItemKey(1 * column + 1,u8"名称");
        this->changeItemKey(2 * column + 1,u8"中心点");
        this->changeItemKey(3 * column + 1,u8"经度(°)");
        this->changeItemKey(4 * column + 1,u8"纬度(°)");
        this->changeItemKey(5 * column + 1,u8"高度(Km)");
        this->changeItemKey(6 * column + 1,u8"水平半径(Km)");
        this->changeItemKey(7 * column + 1,u8"垂直半径(Km)");
        this->changeItemKey(8 * column + 1,u8"面积(Km^2)");
    }
    else if(type == 4){
        //dealRowCount(9);
        this->changeItemKey(0 * column,u8"编号");
        this->changeItemKey(1 * column + 1,u8"名称");
        this->changeItemKey(2 * column + 1,u8"中心点");
        this->changeItemKey(3 * column + 1,u8"经度(°)");
        this->changeItemKey(4 * column + 1,u8"纬度(°)");
        this->changeItemKey(5 * column + 1,u8"高度(Km)");
        this->changeItemKey(6 * column + 1,u8"宽(Km)");
        this->changeItemKey(7 * column + 1,u8"高(Km)");
        this->changeItemKey(8 * column + 1,u8"面积(Km^2)");
    }
    else if(type == 5){
        dealRowCount(3);
        this->changeItemKey(0 * column,u8"编号");
        this->changeItemKey(1 * column + 1,u8"名称");
        this->changeItemKey(2 * column + 1,u8"顶点数");

        qDebug()<<"--------------"<<m_gLayout->rowCount();
    }
}

void AreaInformationDisplay::dealRowCount(const int &value)
{
    auto count = m_gLayout->rowCount();
    if(count < value){
        auto Index = value - count;
        for(int nIndex = 0; nIndex < Index; ++nIndex){
            this->addItem(nIndex + count, u8"" ,u8"");
        }
        repaint();
        qDebug()<<"changed"<<m_gLayout->rowCount()<<value;
    }
    else if(count > value){
        auto Index = count - value;
        for(int nIndex = 0; nIndex < Index; ++nIndex){
            qDebug()<<"remove" << count - nIndex - 1;
            this->removeItem(count - nIndex);
        }
        qDebug()<<"removechagned"<<m_gLayout->rowCount()<<value;
    }
    else{
        qDebug()<<"NothingChanged";
    }
}
