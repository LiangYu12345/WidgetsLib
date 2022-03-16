#ifndef F35WEAPONCONFIGURE_H
#define F35WEAPONCONFIGURE_H

#include "widgetslib_global.h"
#include <QWidget>
#include "missileconfigure.h"

class WIDGETSLIB_EXPORT F35WeaponConfigure : public MissileConfigure
{
    Q_OBJECT
public:
    explicit F35WeaponConfigure(QWidget *parent = nullptr);
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

#endif // F35WEAPONCONFIGURE_H
