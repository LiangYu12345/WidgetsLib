#ifndef MISSILE_H
#define MISSILE_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QMouseEvent>

class WIDGETSLIB_EXPORT Missile : public QWidget
{
    Q_OBJECT
public:
    enum MissileType{
        Empty,Infrare,Radar
    };
    Missile(QWidget * parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent * e) override;
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
    virtual void resizeEvent(QResizeEvent * e) override;
    virtual QSize sizeHint() const override;
signals:
    void clicked(bool checked);
    void doubleClicked();
protected:
    QColor m_painterColor;
    bool m_checked;
private:
    void singleClicked();
private:
    QTimer *m_time;
};

#endif // MISSILE_H
