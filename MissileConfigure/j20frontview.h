#ifndef J20FRONTVIEW_H
#define J20FRONTVIEW_H

#include "widgetslib_global.h"
#include <QWidget>
#include "missileconfigure.h"

class WIDGETSLIB_EXPORT J20FrontView : public MissileConfigure
{
public:
    explicit J20FrontView(QWidget *parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent *e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
    virtual void resizeEvent(QResizeEvent *e) override;
    virtual QSize sizeHint() const override;
    virtual void replaceMissie(int mount, Missile *curMissile) override;
private:
    void updateLayout();
private:
    QPainterPath m_path;
};

#endif // J20FRONTVIEW_H
