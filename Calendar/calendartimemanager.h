#ifndef CALENDARTIMEMANAGER_H
#define CALENDARTIMEMANAGER_H

#include "widgetslib_global.h"
#include <QWidget>

class WIDGETSLIB_EXPORT CalendarTimeManager : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarTimeManager(QWidget *parent = nullptr);

signals:

private:
    QWidget     *m_simulatWidget;
    QWidget     *m_systemWidget;
};

#endif // CALENDARTIMEMANAGER_H
