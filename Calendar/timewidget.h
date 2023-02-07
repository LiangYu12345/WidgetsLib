#ifndef TIMEWIDGET_H
#define TIMEWIDGET_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QPushButton>
#include "timehand.h"

/*!
 * \brief The TimeWidget class
 * \details 管控时钟数据和时针可拖拽转动改变时钟数值
 */
class WIDGETSLIB_EXPORT TimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimeWidget(QWidget *parent = nullptr);
    ~TimeWidget();

    void setHourValue(const int &hour);
    void setMinuteValue(const int &minute);
    void setSecondValue(const int &second);
    void setS(int second);

public slots:
    void updateDis(double second);
signals:
    void sigTimeChanged(int);
protected:
    virtual void paintEvent(QPaintEvent *e) override;
private:
    void Init();
    void InitConnect();

    // 刷新
    void update();
    // 表盘上下午时间标识
    void detectionTime(const int &hour);
private:

    QGraphicsScene      *m_scene;
    QTimer              *m_timer;       /// < 定时器

    QVector<QPoint>     m_hours;        /// < 构成时针点
    QVector<QPoint>     m_minutes;      /// < 构成分针点
    QVector<QPoint>     m_seconds;      /// < 构成秒针点

    TimeHand            *m_hourHand;    /// < 时针
    TimeHand            *m_minuteHand;  /// < 分针
    TimeHand            *m_secondHand;  /// < 秒针

    QColor              m_hourColor;
    QColor              m_minuteColor;
    QColor              m_secondColor;

    double              m_hourValue;    /// < 时针数值
    double              m_minuteValue;  /// < 分针数值
    double              m_secondValue;  /// < 秒针数值

    QTime               m_time;         /// < 时间数值

    bool                isDrop;         /// < 拖拽

    QPushButton         *m_amBtn;       /// < 上午
    QPushButton         *m_pmBtn;       /// < 下午
};

#endif // TIMEWIDGET_H
