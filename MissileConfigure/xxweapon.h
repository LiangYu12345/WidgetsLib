#ifndef XXWEAPON_H
#define XXWEAPON_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QMouseEvent>
#include "missile.h"

class WIDGETSLIB_EXPORT XXWeapon : public Missile
{
    Q_OBJECT
public:
    explicit XXWeapon(QWidget * parent = nullptr);
protected:
    void paintEvent(QPaintEvent * e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
private:
    QPainterPath m_path;
    bool m_checked = false;
};

#endif // XXWEAPON_H
