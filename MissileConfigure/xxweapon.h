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
    virtual QSize sizeHint() const override;
private:
    QPainterPath m_path;
};

#endif // XXWEAPON_H
