#ifndef WEAPONCONFIGURE_H
#define WEAPONCONFIGURE_H

#include "widgetslib_global.h"
#include <QWidget>
#include <QMouseEvent>
#include "xxweapon.h"

class WIDGETSLIB_EXPORT WeaponConfigure : public QWidget
{
    Q_OBJECT

public:
    struct WeaponSpace{
        QPointF   position;
        QSizeF    size;
        XXWeapon *xx;
    };
    WeaponConfigure(QWidget * parent = nullptr);

    void setWeapon(int mount, const WeaponSpace &weapon);
    void removeWeapon(int mount);
    void clearWeapon();
    XXWeapon *weapon(int mount);
    WeaponSpace *weaponMount(int mount);

    /// 移动武器到指定位置
    /// \param point x对应机头方向 y对应机翼方向 单位：米
    void setWeaponPosition(int mount,QPointF pos);
    QPointF getWeaponPosition(int mount);
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
private:
    int mountWeaponIndex(Missile* mis);
    void onWeaponClicked(bool check);
    void onWeaponDoubleClicked();
signals:
    void addedWeapon(int mount);
    void removedWeapon(int mount);
    void clearedWeapon();
    void changedWeapon(int mount);
    void checkedWeapon(int mount, bool &check);
    void toggled(int mount);
protected:
    QMap<int, WeaponSpace> m_weaponMap;
    QColor                m_painterColor;
};

#endif // WEAPONCONFIGURE_H
