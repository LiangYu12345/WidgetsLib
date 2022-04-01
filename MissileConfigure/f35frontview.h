#ifndef F35FRONTVIEW_H
#define F35FRONTVIEW_H

#include "widgetslib_global.h"
#include <QWidget>
#include "weaponconfigure.h"

class WIDGETSLIB_EXPORT F35FrontView : public WeaponConfigure
{
public:
    explicit F35FrontView(QWidget *parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent *e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
    virtual void resizeEvent(QResizeEvent *e) override;
    virtual QSize sizeHint() const override;
private:
    QPainterPath m_path;
};

#endif // F35FRONTVIEW_H
