#include "calendartimemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QDate>
#include <QDebug>

CalendarTimeManager::CalendarTimeManager(QWidget *parent)
    : QWidget{parent}
{
    Init();
    InitConnect();
}

void CalendarTimeManager::simUpdate(const int &second)
{
    auto simulatLastTime = m_simulatTimeEdit->dateTime().date();
    QTime time(0, 0, 0);
    auto temp = time.addSecs(second);
    m_simulatTimeEdit->setDateTime({simulatLastTime, temp});

}

void CalendarTimeManager::sysUpdate(const int &second)
{
    auto systemLastTime = m_systemTimeEdit->dateTime().date();
    QTime time(0, 0, 0);
    auto temp = time.addSecs(second);
    m_systemTimeEdit->setDateTime({systemLastTime, temp});
}

void CalendarTimeManager::setSimulateTimeValue(const QDateTime &value)
{
    auto date = value.date();
    auto hour = value.time().hour();
    auto minute = value.time().minute();
    auto second = value.time().second();
    m_simulatTimeEdit->setDateTime(value);

    m_simCalendarWidget->setCalendarValue(date);
    m_simTimeWidget->setS(hour * 3600 + minute * 60 + second);
}

void CalendarTimeManager::setSystemTimeValue(const QDateTime &value)
{
    auto date = value.date();
    auto hour = value.time().hour();
    auto minute = value.time().minute();
    auto second = value.time().second();
    m_systemTimeEdit->setDateTime(value);

    m_sysCalendarWidget->setCalendarValue(date);
    m_sysTimeWidget->setS(hour * 3600 + minute * 60 + second);
}

bool CalendarTimeManager::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == m_simulatTimeEdit && event->type() == QEvent::MouseButtonPress){
        m_isToggle =! m_isToggle;
        m_curTimeType = 1;
        onCtrlShow();
        return true;
    }
    else if(obj == m_systemTimeEdit && event->type() == QEvent::MouseButtonPress){
        m_isToggle =! m_isToggle;
        m_curTimeType = 2;
        onCtrlShow();
        return true;
    }
    else if(obj == m_simulatTimeEdit && event->type() == QEvent::MouseButtonDblClick){
        return true;
    }
    else if(obj == m_systemTimeEdit && event->type() == QEvent::MouseButtonDblClick){
        return true;
    }

    return false;
}

void CalendarTimeManager::Init()
{
    m_simCalendarWidget = new CalendarWidght();
    m_sysCalendarWidget = new CalendarWidght();
    m_simTimeWidget = new TimeWidget();
    m_sysTimeWidget = new TimeWidget();
    m_simCalendarWidget->hide();
    m_sysCalendarWidget->hide();
    m_simTimeWidget->hide();
    m_sysTimeWidget->hide();

    auto vLayout = new QVBoxLayout;
    auto hPart1Layout = new QHBoxLayout;
    auto hPart2Layout = new QHBoxLayout;
#ifdef TextEnglish
    auto simulatLabel = new QLabel(u8"Simulation Time:");
    auto systemLabel = new QLabel(u8"System Time:");
#else
    auto simulatLabel = new QLabel(u8"仿真时间:");
    auto systemLabel = new QLabel(u8"系统时间:");
#endif

    m_simulatTimeEdit = new QDateTimeEdit;
    m_systemTimeEdit = new QDateTimeEdit;
    m_simulatTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    m_simulatTimeEdit->setCalendarPopup(true);

    m_systemTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    m_systemTimeEdit->setCalendarPopup(true);

    hPart1Layout->addWidget(simulatLabel);
    hPart1Layout->addWidget(m_simulatTimeEdit);
    hPart2Layout->addWidget(systemLabel);
    hPart2Layout->addWidget(m_systemTimeEdit);

    vLayout->addLayout(hPart1Layout);
    vLayout->addLayout(hPart2Layout);

    this->setLayout(vLayout);

    m_simulatTimeEdit->installEventFilter(this);
    m_systemTimeEdit->installEventFilter(this);

    this->setStyleSheet("QLabel{"
                           "background-color: rgba(100, 100, 100, 100);"
                           "color: white;"
                           "font: 12pt \"Microsoft Yahei\";"
                           "}");

    /// 初始化数据
    QDateTime date(QDate(1970,01,01));
    setSimulateTimeValue(date);
    setSystemTimeValue({QDate::currentDate(), QTime::currentTime()});
}

void CalendarTimeManager::InitConnect()
{
    connect(m_simTimeWidget, &TimeWidget::sigTimeChanged, this, &CalendarTimeManager::simUpdate);
    connect(m_sysTimeWidget, &TimeWidget::sigTimeChanged, this, &CalendarTimeManager::sysUpdate);

    connect(m_simCalendarWidget, &CalendarWidght::calendarSureBtnClicked, this, [=](const QDate &date){
        m_simulatTimeEdit->setDate(date);
        m_simCalendarWidget->hide();
    });
    connect(m_sysCalendarWidget, &CalendarWidght::calendarSureBtnClicked, this, [=](const QDate &date){
        m_systemTimeEdit->setDate(date);
        m_sysCalendarWidget->hide();
    });
    connect(m_sysCalendarWidget, &CalendarWidght::calendarCancelBtnClicked, this, [=](){
        m_simCalendarWidget->hide();
    });
    connect(m_sysCalendarWidget, &CalendarWidght::calendarCancelBtnClicked, this, [=](){
        m_sysCalendarWidget->hide();
    });
}

void CalendarTimeManager::onCtrlShow()
{
    if(m_isToggle && m_curTimeType == 1){
        m_simCalendarWidget->show();
        m_simTimeWidget->show();

        m_sysCalendarWidget->hide();
        m_sysTimeWidget->hide();
    }
    else if(m_isToggle && m_curTimeType == 2){
        m_sysCalendarWidget->show();
        m_sysTimeWidget->show();

        m_simCalendarWidget->hide();
        m_simTimeWidget->hide();
    }
    else{
        m_simCalendarWidget->hide();
        m_simTimeWidget->hide();
        m_sysCalendarWidget->hide();
        m_sysTimeWidget->hide();
    }
}
