#ifndef J20FRONTVIEW_H
#define J20FRONTVIEW_H

#include "widgetslib_global.h"
#include <QWidget>
#include "weaponconfigure.h"

class WIDGETSLIB_EXPORT J20FrontView : public WeaponConfigure
{
public:
    explicit J20FrontView(QWidget *parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent *e) override;
    virtual void resizeEvent(QResizeEvent *e) override;
    virtual QSize sizeHint() const override;
    virtual void mouseDoubleClickEvent(QMouseEvent * e) override;
private:
    QPainterPath m_path;
};

#endif // J20FRONTVIEW_H
