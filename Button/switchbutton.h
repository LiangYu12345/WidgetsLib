#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H


#include "widgetslib_global.h"
#include <QWidget>
#include <QMouseEvent>
#include <QTimer>

/*!
 * \brief The SwitchButton class
 * \details 用于时间管理开关控制按钮
 */
class WIDGETSLIB_EXPORT SwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget * parent = nullptr);
    explicit SwitchButton(const QString &opentext,const QString &closetext, QWidget *parent = nullptr);

    bool isTooggle();
    void setToggle(bool checked);

    void setBackgroundColor(QColor color);
    void setCheckedColor(QColor color);
    void setDisabledColor(QColor color);

    void setChangedTimeTotal(const double &value);
protected:
    void paintEvent(QPaintEvent * e) override;
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    void resizeEvent(QResizeEvent * e) override;

    virtual QSize sizeHint() const override;
    virtual QSize minimumSizeHint() const override;
signals:
    void checked(bool checked);
private:
    void onTimeout();
private:
    bool m_checked;
    QColor m_backgroundColor;
    QColor m_checkedColor;
    QColor m_disabledColor;
    QColor m_thumbColor;
    double m_radius;
    double m_height;
    double m_marigin;
    QString m_opentext;
    QString m_closetext;

    double m_timetotal;
    double m_actortime;
    double m_interval;

    QTimer m_timer;
};

#endif // SWITCHBUTTON_H
