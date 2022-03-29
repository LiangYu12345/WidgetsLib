#include "missileconfigure.h"
#include <QPainter>

MissileConfigure::MissileConfigure(QWidget *parent)
    : QWidget(parent),
      m_painterColor(Qt::yellow)
{

}

void MissileConfigure::setMissile(int mount, Missile *mis)
{
    if(!mis)
        return;

    if(m_missileMap.value(mount)) {
        delete m_missileMap.value(mount);

        connect(mis, &Missile::clicked, this, &MissileConfigure::onMissileClicked);
        connect(mis, &Missile::doubleClicked, this, &MissileConfigure::onMissileDoubleClicked);
        mis->setParent(this);
        m_missileMap.insert(mount, mis);
        emit changedMissile(mount);
    }
    else {
        connect(mis, &Missile::clicked, this, &MissileConfigure::onMissileClicked);
        connect(mis, &Missile::doubleClicked, this, &MissileConfigure::onMissileDoubleClicked);
        mis->setParent(this);
        m_missileMap.insert(mount, mis);
        emit addedMissile(mount);
    }
    mis->show();
}

void MissileConfigure::removeMissile(int mount)
{
    if(!m_missileMap.value(mount))
        return;
    delete m_missileMap.value(mount);
    emit removedMissile(mount);
}

void MissileConfigure::clearMissile()
{
    qDeleteAll(m_missileMap);
    m_missileMap.clear();
    emit clearedMissile();
}

Missile *MissileConfigure::missile(int mount)
{
    if(m_missileMap.contains(mount))
        return m_missileMap.find(mount).value();
    return nullptr;
}

void MissileConfigure::setWeapon(int mount, const WeaponSpace &weapon)
{
    if(!weapon.xx)
        return;

    if(m_weaponMap.value(mount).xx) {
        delete m_weaponMap.value(mount).xx;

        connect(weapon.xx, &Missile::clicked, this, &MissileConfigure::onWeaponClicked);
        connect(weapon.xx, &Missile::doubleClicked, this, &MissileConfigure::onWeaponDoubleClicked);
        weapon.xx->setParent(this);
        m_weaponMap.insert(mount, weapon);
        emit changedWeapon(mount);
    }
    else {
        connect(weapon.xx, &Missile::clicked, this, &MissileConfigure::onWeaponClicked);
        connect(weapon.xx, &Missile::doubleClicked, this, &MissileConfigure::onWeaponDoubleClicked);
        weapon.xx->setParent(this);
        m_weaponMap.insert(mount, weapon);
        emit addedWeapon(mount);
    }
    weapon.xx->show();
}

void MissileConfigure::removeWeapon(int mount)
{
    if(!m_weaponMap.value(mount).xx)
        return;
    delete m_weaponMap.value(mount).xx;
    m_weaponMap.remove(mount);
    emit removedWeapon(mount);
}

void MissileConfigure::clearWeapon()
{
    for(auto item : qAsConst(m_weaponMap))
        delete item.xx;
    m_weaponMap.clear();
    emit clearedWeapon();
}

XXWeapon *MissileConfigure::weapon(int mount)
{
    if(m_weaponMap.contains(mount))
        return m_weaponMap.find(mount).value().xx;
    return nullptr;
}

void MissileConfigure::mouseDoubleClickEvent(QMouseEvent *e)
{
    e->accept();
}

void MissileConfigure::onMissileClicked(bool check)
{
    auto mis = qobject_cast<Missile*>(sender());
    int mount = mountMissileIndex(mis);
    emit checkedMissile(mount, check);
}

void MissileConfigure::onMissileDoubleClicked()
{
    auto mis = qobject_cast<Missile*>(sender());
    if(!mis)
        return;

    replaceMissie(mountMissileIndex(mis), mis);
}

int MissileConfigure::mountMissileIndex(Missile *mis)
{
    QMapIterator<int, Missile*> iter(m_missileMap);
    while(iter.hasNext()) {
        auto item = iter.next();
        if(item.value() == mis)
            return item.key();
    }
    return -1;
}

int MissileConfigure::mountWeaponIndex(Missile *mis)
{
    QMapIterator<int, WeaponSpace> iter(m_weaponMap);
    while(iter.hasNext()) {
        auto item = iter.next();
        if(item.value().xx == mis)
            return item.key();
    }
    return -1;
}

void MissileConfigure::onWeaponClicked(bool check)
{
    auto weapon = qobject_cast<Missile*>(sender());
    int mount = mountWeaponIndex(weapon);
    emit checkedWeapon(mount, check);
}

void MissileConfigure::onWeaponDoubleClicked()
{
    auto mis = qobject_cast<Missile*>(sender());
    if(!mis)
        return;

    int mount = mountWeaponIndex(mis);
    delete mis;
    m_weaponMap.remove(mount);
    emit removedWeapon(mount);
}
