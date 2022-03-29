#ifndef F35MISSILECONFIGURE_H
#define F35MISSILECONFIGURE_H


#include "widgetslib_global.h"
#include <QWidget>
#include <QMouseEvent>
#include "missileconfigure.h"

class WIDGETSLIB_EXPORT F35MissileConfigure : public MissileConfigure
{
    Q_OBJECT
public:
    explicit F35MissileConfigure(QWidget * parent = nullptr);
    void updateLayout();
protected:
    virtual void paintEvent(QPaintEvent * e) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual QSize sizeHint() const override;
    virtual void replaceMissie(int mount, Missile *curMissile) override;
private:
    QPainterPath m_path;
};

#endif // F35MISSILECONFIGURE_H
