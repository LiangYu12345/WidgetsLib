#ifndef F35WEAPONCONFIGURE_H
#define F35WEAPONCONFIGURE_H

#include "widgetslib_global.h"
#include "weaponconfigure.h"

class WIDGETSLIB_EXPORT F35WeaponConfigure : public WeaponConfigure
{
    Q_OBJECT
public:
    explicit F35WeaponConfigure(QWidget *parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent *e) override;
    virtual void resizeEvent(QResizeEvent *e) override;
    virtual QSize sizeHint() const override;
    virtual void mouseDoubleClickEvent(QMouseEvent * e) override;
private:
    bool isPointInMatrix(QPointF p1, QPointF p2, QPointF p3, QPointF p4, QPointF p);
    double getCross(QPointF p1, QPointF p2, QPointF p);
private:
    QPainterPath m_path;
};

#endif // F35WEAPONCONFIGURE_H
