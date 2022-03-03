#ifndef EMPTYDMISSILE_H
#define EMPTYDMISSILE_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QMouseEvent>
#include "missile.h"

class WIDGETSLIB_EXPORT EmptyMissile : public Missile
{
    Q_OBJECT
public:
    explicit EmptyMissile(QWidget * parent = nullptr);
protected:
    void paintEvent(QPaintEvent * e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
private:
    QPainterPath m_path;
};

#endif // EMPTYDMISSILE_H
