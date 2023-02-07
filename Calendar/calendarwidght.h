#ifndef CALENDARWIDGHT_H
#define CALENDARWIDGHT_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QProxyStyle>
#include <QCalendarWidget>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include <QPainter>

class WIDGETSLIB_EXPORT CalendarWidght : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit CalendarWidght(QWidget *parent = nullptr);

signals:
    void calendarCellClicked(const QDate &data);
protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;
private:
    void Init();
    void InitConnect();

    // 设置时间文本
    void setDataLabelText(const int year, const int month);
private:
    QPushButton     *m_leftYearBtn;
    QPushButton     *m_leftMonthBtn;
    QPushButton     *m_rightYearBtn;
    QPushButton     *m_rightMonthBtn;

    QLabel          *m_dataLabel;

    int             m_month;
};

#endif // CALENDARWIDGHT_H
