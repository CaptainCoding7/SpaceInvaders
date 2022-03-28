#include <QTimer>
#include <QGraphicsScene>

#include "components.h"

CCannon::CCannon(EColor eColor, QGraphicsItem *pParent) : QGraphicsPixmapItem(pParent)
{
    setColor((eColor));
}

void CCannon::shoot()
{
    CBullet * pBullet = new CBullet(m_eColor);
    connect(pBullet, &CBullet::sigIncreaseScore, this, &CCannon::sigIncreaseScore);
    connect(pBullet, &CBullet::sigDecreaseScore, this, &CCannon::sigDecreaseScore);

    pBullet->setPos(x()+27, y()-10);
    scene()->addItem(pBullet);


}

EColor CCannon::getColor() const
{
    return m_eColor;
}

vois CCannon::setColor(EColor eColor)
{
    m_eColor = eColor;

    switch(eColor)
    {
        case eColor::Red:
        {
            QPixmap oPixmap(":/Ressources/RedCannon.png");
            break;
        }
    case eColor::Pink:
        {
            QPixmap oPixmap(":/Ressources/PinkCannon.png");
            break;
        }
    case eColor::Blue:
        {
            QPixmap oPixmap(":/Ressources/BlueCannon.png");
            break;
        }
    default:
        {
            QPixmap oPixmap(":/Ressources/RedCannon.png");
            break;
        }

    }

    setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));



}

/**********************************************************************/

CAlien::CAlien(Ecolor eColor, QGraphicsItem *pParent)
{
    setColor(eColor);
    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &CAlien::onMove);
    pTimer->start((gAlienSpeed));
}

EColor CAlien::getColor() const
{
    return m_eColor;
}

void CAlien::setColor(EColor eColor)
{
    m_eColor = eColor;

    switch(eColor)
    {
        case eColor::Red:
        {
            QPixmap oPixmap(":/Ressources/RedAlien.png");
            break;
        }
    case eColor::Pink:
        {
            QPixmap oPixmap(":/Ressources/PinkAlien.png");
            break;
        }
    case eColor::Blue:
        {
            QPixmap oPixmap(":/Ressources/BlueAlien.png");
            break;
        }
    }

    setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));

}

void CAlien::onMove()
{
    setPos(x(), y() + 5);
    if(pos().y() >= (scene()->height() - gCannonSize.height()))
    {
        scene()->removeItem(this);
        emit sigDecreaseHealth();
        delete this;

    }

    QList<QGraphicsItem*> listCollidingItem = collidingItems();
    for (auto const pItem : listCollidingItem)
    {
        if(dynamic_cast<CCannon*>(pItem))
            emit sigGameOver();
    }


}

/**********************************************************************/


CBullet::CBullet(Ecolor eColor, QGraphicsItem *pParent)
{

}

EColor CBullet::getColor() const
{

}

void CBullet::setColor(EColor eColor)
{

}

void CBullet::onMove()
{

}

/**********************************************************************/


CPoints::CPoints(Ecolor eColor, QGraphicsItem *pParent)
{

}

void CPoints::increaseScore()
{

}

void CPoints::decreaseScore()
{

}

void CPoints::decreaseHealth()
{

}

int CPoints::getHealth() const
{

}

int CPoints::getScore() const
{

}

void CPoints::reset()
{

}


