#ifndef MISSILECONFIGURE_H
#define MISSILECONFIGURE_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QMouseEvent>
#include "missile.h"
#include "infraredmissile.h"
#include "radarmissile.h"
#include "emptymissile.h"
#include "xxweapon.h"

class WIDGETSLIB_EXPORT MissileConfigure : public QWidget
{
    Q_OBJECT
public:
    struct WeaponSpace{
        QPointF   position;
        QSizeF    size;
        XXWeapon *xx;
    };
    MissileConfigure(QWidget * parent = nullptr);

    void setMissile(int mount, Missile *mis);
    void removeMissile(int mount);
    void clearMissile();
    Missile *missile(int mount);

    void setWeapon(int mount, const WeaponSpace &weapon);
    void removeWeapon(int mount);
    void clearWeapon();
    XXWeapon *weapon(int mount);
    WeaponSpace *weaponMount(int mount);

    /// 移动武器到指定位置 \param point x对应机头方向 y对应机翼方向 单位：米
    void setWeaponPosition(int mount,QPointF pos);
    QPointF getWeaponPosition(int mount);
protected:
    virtual void replaceMissie(int mount, Missile *curMissile) = 0;
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
private:
    void onMissileClicked(bool checked);
    void onMissileDoubleClicked();
    int mountMissileIndex(Missile* mis);
    int mountWeaponIndex(Missile* mis);

    void onWeaponClicked(bool check);
    void onWeaponDoubleClicked();
signals:
    void addedMissile(int mount);
    void removedMissile(int mount);
    void clearedMissile();
    void changedMissile(int mount);
    void checkedMissile(int mount, bool &check);

    void addedWeapon(int mount);
    void removedWeapon(int mount);
    void clearedWeapon();
    void changedWeapon(int mount);
    void checkedWeapon(int mount, bool &check);
    void toggled(int mount);

protected:
    QMap<int, Missile*>   m_missileMap;
    QMap<int, WeaponSpace> m_weaponMap;
    QColor                m_painterColor;
};

#endif // J20MISSILECONFIGURE_H
