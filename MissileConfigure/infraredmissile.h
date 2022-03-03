#ifndef INFRAREDMISSILE_H
#define INFRAREDMISSILE_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include "missile.h"

class WIDGETSLIB_EXPORT InfraredMissile : public Missile
{
    Q_OBJECT
public:
    explicit InfraredMissile(QWidget * parent = nullptr);
protected:
    void paintEvent(QPaintEvent * e) override;
private:
    QPainterPath m_path;
};

#endif // INFRAREDMISSILE_H
