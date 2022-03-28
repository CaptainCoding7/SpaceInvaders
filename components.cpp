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
