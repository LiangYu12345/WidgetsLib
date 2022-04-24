#ifndef RADARMISSILE_H
#define RADARMISSILE_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QMouseEvent>
#include "missile.h"

class WIDGETSLIB_EXPORT RadarMissile : public Missile
{
    Q_OBJECT
public:
    explicit RadarMissile(QWidget * parent = nullptr);
protected:
    void paintEvent(QPaintEvent * e) override;
private:
    QPainterPath m_path;
};

#endif // RADARMISSILE_H
