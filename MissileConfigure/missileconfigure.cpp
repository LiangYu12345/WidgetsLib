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
        emit changed(mount, mis);
    }
    else {
        connect(mis, &Missile::clicked, this, &MissileConfigure::onMissileClicked);
        connect(mis, &Missile::doubleClicked, this, &MissileConfigure::onMissileDoubleClicked);
        mis->setParent(this);
        m_missileMap.insert(mount, mis);
        emit added(mount, mis);
    }
    mis->show();
}

void MissileConfigure::removeMissile(int mount)
{
    if(!m_missileMap.value(mount))
        return;
    delete m_missileMap.value(mount);
    emit removed(mount);
}

void MissileConfigure::clear()
{
    qDeleteAll(m_missileMap);
    m_missileMap.clear();
    emit cleared();
}

void MissileConfigure::onMissileClicked(bool check)
{
    auto mis = qobject_cast<Missile*>(sender());
    int mount = mountIndex(mis);
    emit checked(mount, mis, check);
}

void MissileConfigure::onMissileDoubleClicked()
{
    auto mis = qobject_cast<Missile*>(sender());
    if(!mis)
        return;

    replaceMissie(mountIndex(mis), mis);
}

int MissileConfigure::mountIndex(Missile *mis)
{
    QMapIterator<int, Missile*> iter(m_missileMap);
    while(iter.hasNext()) {
        auto item = iter.next();
        if(item.value() == mis)
            return item.key();
    }
    return -1;
}
