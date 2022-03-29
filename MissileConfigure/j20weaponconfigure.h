#ifndef J20WEAPONCONFIGURE_H
#define J20WEAPONCONFIGURE_H

#include "widgetslib_global.h"
#include "missileconfigure.h"

class WIDGETSLIB_EXPORT J20WeaponConfigure : public MissileConfigure
{
    Q_OBJECT
public:
    explicit J20WeaponConfigure(QWidget * parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent * e) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual QSize sizeHint() const override;
    virtual void replaceMissie(int mount, Missile *curMissile) override;
    virtual void mouseDoubleClickEvent(QMouseEvent * e) override;
private:
    bool isPointInMatrix(QPointF p1, QPointF p2, QPointF p3, QPointF p4, QPointF p);
    double getCross(QPointF p1, QPointF p2, QPointF p);
private:
    QPainterPath m_path;
};

#endif // J20WEAPONCONFIGURE_H
