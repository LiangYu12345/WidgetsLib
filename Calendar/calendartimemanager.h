#ifndef CALENDARTIMEMANAGER_H
#define CALENDARTIMEMANAGER_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QDateTimeEdit>
#include <QLabel>
#include "calendarwidght.h"
#include "timewidget.h"

//#define TextEnglish

class WIDGETSLIB_EXPORT CalendarTimeManager : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarTimeManager(QWidget *parent = nullptr);

    /// 时钟定时器跑 回传总秒 计算是否天数变化
    void simUpdate(const int &second);
    void sysUpdate(const int &second);

    /// 设置仿真时间的数值
    void setSimulateTimeValue(const QDateTime &value);
    /// 设置系统时间的数值
    void setSystemTimeValue(const QDateTime &value);
signals:

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event) override;
private:
    void Init();
    void InitConnect();

    void onCtrlShow();
private:
    QWidget             *m_simulatWidget;
    QWidget             *m_systemWidget;

    QLabel              *m_simulatLabel;
    QLabel              *m_systemLabel;

    QDateTimeEdit       *m_simulatTimeEdit;
    QDateTimeEdit       *m_systemTimeEdit;

    CalendarWidght      *m_simCalendarWidget;
    CalendarWidght      *m_sysCalendarWidget;
    TimeWidget          *m_simTimeWidget;
    TimeWidget          *m_sysTimeWidget;

    bool                m_isToggle = false;
    int                 m_curTimeType = 1;
};

#endif // CALENDARTIMEMANAGER_H
