#include "weaponconfigure.h"
#include <QDebug>
WeaponConfigure::WeaponConfigure(QWidget * parent)
    :QWidget(parent),
    m_painterColor(Qt::yellow)
{

}

void WeaponConfigure::setWeapon(int mount, const WeaponSpace &weapon)
{
    if(!weapon.xx)
        return;

    if(m_weaponMap.value(mount).xx) {
        delete m_weaponMap.value(mount).xx;

        connect(weapon.xx, &Missile::clicked, this, &WeaponConfigure::onWeaponClicked);
        connect(weapon.xx, &Missile::doubleClicked, this, &WeaponConfigure::onWeaponDoubleClicked);
        weapon.xx->setParent(this);
        m_weaponMap.insert(mount, weapon);
        emit changedWeapon(mount);
    }
    else {
        connect(weapon.xx, &Missile::clicked, this, &WeaponConfigure::onWeaponClicked);
        connect(weapon.xx, &Missile::doubleClicked, this, &WeaponConfigure::onWeaponDoubleClicked);
        weapon.xx->setParent(this);
        m_weaponMap.insert(mount, weapon);
        emit addedWeapon(mount);
    }


    weapon.xx->show();
}

void WeaponConfigure::removeWeapon(int mount)
{
    if(!m_weaponMap.value(mount).xx)
        return;
    delete m_weaponMap.value(mount).xx;
    m_weaponMap.remove(mount);
    emit removedWeapon(mount);
}

void WeaponConfigure::clearWeapon()
{
    for(auto item : qAsConst(m_weaponMap))
        delete item.xx;
    m_weaponMap.clear();
    emit clearedWeapon();
}

XXWeapon *WeaponConfigure::weapon(int mount)
{
    if(m_weaponMap.contains(mount))
        return m_weaponMap.find(mount).value().xx;
    return nullptr;
}

WeaponConfigure::WeaponSpace *WeaponConfigure::weaponMount(int mount)
{
    if(m_weaponMap.contains(mount)){
        return &m_weaponMap.find(mount).value();
    }
    return nullptr;
}

void WeaponConfigure::setWeaponPosition(int mount, QPointF pos)
{
    if(m_weaponMap.contains(mount)){
        auto &item = m_weaponMap.find(mount).value();
        item.position = pos;

        int x = pos.x()*25+150;
        int y = pos.y()*23+230;

        item.xx->move(x,y);
		qDebug() <<"mountId : " << mount << "weaponconfigure : " << "x : " << x  << "y: "<< y;
        update();
    }
}

QPointF WeaponConfigure::getWeaponPosition(int mount)
{
    auto &item = m_weaponMap.find(mount).value();
    QPointF pos = item.position;
	qDebug() << "mountId : " << mount << pos.x() << (pos.x() - 150) / 25 << pos.y() << (pos.y() - 230) / 23;
    pos.setX((pos.x()- 150)/25);
    pos.setY((pos.y() - 230)/23);
    return pos;
}

void WeaponConfigure::mouseDoubleClickEvent(QMouseEvent *e)
{
    e->accept();
}

int WeaponConfigure::mountWeaponIndex(Missile *mis)
{
    QMapIterator<int, WeaponSpace> iter(m_weaponMap);
    while(iter.hasNext()) {
        auto item = iter.next();
        if(item.value().xx == mis)
            return item.key();
    }
    return -1;
}

void WeaponConfigure::onWeaponClicked(bool check)
{
    auto weapon = qobject_cast<Missile*>(sender());
    int mount = mountWeaponIndex(weapon);
    emit checkedWeapon(mount, check);
}

void WeaponConfigure::onWeaponDoubleClicked()
{
    auto mis = qobject_cast<Missile*>(sender());
    if(!mis)
        return;

    int mount = mountWeaponIndex(mis);
    delete mis;
    m_weaponMap.remove(mount);
    emit removedWeapon(mount);
}
