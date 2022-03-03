#ifndef MISSILECONFIGURE_H
#define MISSILECONFIGURE_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QMouseEvent>
#include "missile.h"
#include "infraredmissile.h"
#include "radarmissile.h"
#include "emptymissile.h"

class WIDGETSLIB_EXPORT MissileConfigure : public QWidget
{
    Q_OBJECT
public:
    MissileConfigure(QWidget * parent = nullptr);

    void setMissile(int mount, Missile *mis);
    void removeMissile(int mount);
    void clear();

    Missile *missile(int mount);

protected:
    virtual void replaceMissie(int mount, Missile *curMissile) = 0;

private:
    void onMissileClicked(bool checked);
    void onMissileDoubleClicked();

    int mountIndex(Missile* mis);

signals:
    void added(int mount, Missile *mis);
    void removed(int mount);
    void cleared();
    void changed(int mount, Missile *mis);
    void checked(int mount, Missile *mis, bool &check);
    void toggled(int mount, Missile *mis);

protected:
    QMap<int, Missile*> m_missileMap;
    QColor              m_painterColor;
};

#endif // J20MISSILECONFIGURE_H
