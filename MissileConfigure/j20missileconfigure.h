#ifndef J20MISSILECONFIGURE_H
#define J20MISSILECONFIGURE_H


#include "widgetslib_global.h"
#include <QWidget>
#include <QMouseEvent>
#include "missileconfigure.h"

class WIDGETSLIB_EXPORT J20MissileConfigure : public MissileConfigure
{
    Q_OBJECT
public:
    explicit J20MissileConfigure(QWidget * parent = nullptr);
    void updateLayout();
protected:
    virtual void paintEvent(QPaintEvent * e) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual QSize sizeHint() const override;

    virtual void replaceMissie(int mount, Missile *curMissile) override;
private:
    QPainterPath m_path;
};

#endif // J20MISSILECONFIGURE_H
