#include "areainformationdisplay.h"

AreaInformationDisplay::AreaInformationDisplay(QWidget *parent)
    : QWidget{parent}
{
    m_gLayout = new QGridLayout;

//    m_gLayout->setHorizontalSpacing(25);
//    m_gLayout->setVerticalSpacing(10);
    this->setLayout(m_gLayout);

    this->setAttribute(Qt::WA_TransparentForMouseEvents,true);
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
    auto item = m_gLayout->itemAt(Index);
    m_gLayout->removeItem(item);
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

void AreaInformationDisplay::changeItemVal(int Index, const QString &value)
{
    auto layoutValItem = m_gLayout->itemAtPosition(Index,1);
    auto labelVal = static_cast<QLabel *>(layoutValItem->widget());
    labelVal->setText(value);
}
