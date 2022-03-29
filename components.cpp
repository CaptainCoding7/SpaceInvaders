#include <QTimer>
#include <QGraphicsScene>

#include "components.h"


/**********************************************************************/

CCannon::CCannon(EColor eColor, QGraphicsItem *pParent) : QGraphicsPixmapItem(pParent)
{
    setColor((eColor));
}

void CCannon::shoot()
{
    CBullet* pBullet = new CBullet(m_eColor);
    connect(pBullet, &CBullet::sigIncreaseScore, this, &CCannon::sigIncreaseScore);
    connect(pBullet, &CBullet::sigDecreaseScore, this, &CCannon::sigDecreaseScore);

    // the bullet position is changed
    pBullet->setPos(x()+27, y()-10);
    // we add the bullet to the scene
    scene()->addItem(pBullet);

}

EColor CCannon::getColor() const
{
    return m_eColor;
}

void CCannon::setColor(EColor eColor)
{
    m_eColor = eColor;

    switch(eColor)
    {
    case EColor::Red:
        {
            QPixmap oPixmap(":/Resources/RedCannon.png");
            setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
            break;
        }
    case EColor::Pink:
        {
            QPixmap oPixmap(":/Resources/PinkCannon.png");
            setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
            break;
        }
    case EColor::Blue:
        {
            QPixmap oPixmap(":/Resources/BlueCannon.png");
            setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
            break;
        }
    default:
        {
            QPixmap oPixmap(":/Resources/RedCannon.png");
            setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
            m_eColor=EColor::Red;
            break;
        }

    }

    //setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));

}

/**********************************************************************/

CAlien::CAlien(EColor eColor, QGraphicsItem *pParent)
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
        case EColor::Red:
            {
                QPixmap oPixmap(":/Resources/RedAlien.png");
                setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
                break;
            }
        case EColor::Pink:
            {
                QPixmap oPixmap(":/Resources/PinkAlien.png");
                setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
                break;
            }
        case EColor::Blue:
            {
                QPixmap oPixmap(":/Resources/BlueAlien.png");
                setPixmap(oPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio));
                break;
            }
    }

}

void CAlien::onMove()
{
    // the alien position is changed
    setPos(x(), y() + 5);
    // if the alien reached the ground
    if(pos().y() >= (scene()->height() - gCannonSize.height()))
    {
        // ... it is removed
        scene()->removeItem(this);
        // we lose health
        emit sigDecreaseHealth();
        delete this;

    }
    // for all items that collides with the alien
    QList<QGraphicsItem*> listCollidingItem = collidingItems();
    for (auto const pItem : listCollidingItem)
    {
        // ... if it's the cannon, we lose !
        if(dynamic_cast<CCannon*>(pItem))
            emit sigGameOver();
    }


}

/**********************************************************************/


CBullet::CBullet(EColor eColor, QGraphicsItem *pParent): QGraphicsPixmapItem(pParent)
{
    setColor(eColor);
    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &CBullet::onMove);
    pTimer->start((gBulletSpeed));

}

EColor CBullet::getColor() const
{
    return m_eColor;
}

void CBullet::setColor(EColor eColor)
{
    m_eColor = eColor;
    //QPixmap oPixmap();
    //oPixmap.data

    switch(eColor)
    {
        case EColor::Red:
            {
                QPixmap oPixmap(":/Resources/RedBullet.png");
                setPixmap(oPixmap.scaled(QSize(40, 40), Qt::KeepAspectRatio));
                break;
            }
        case EColor::Pink:
            {
                QPixmap oPixmap(":/Resources/PinkBullet.png");
                setPixmap(oPixmap.scaled(QSize(40, 40), Qt::KeepAspectRatio));
                break;
            }
        case EColor::Blue:
            {
                QPixmap oPixmap(":/Resources/BlueBullet.png");
                setPixmap(oPixmap.scaled(QSize(40, 40), Qt::KeepAspectRatio));
                break;
            }
    }


}

void CBullet::onMove()
{

    /* Checking if we hit an alien
     * If we do, it's removed and
     */
    QList<QGraphicsItem*> listCollidingItem = collidingItems();
    for (auto const pItem : listCollidingItem)
    {
        CAlien* pAlien = dynamic_cast<CAlien*>(pItem);
        if(pAlien != nullptr)
        {
            // if we touch an alien with the right color
            if(pAlien->getColor() == getColor())
            {
                scene()->removeItem(pAlien);
                scene()->removeItem(this);
                //the score is increased
                emit sigIncreaseScore();
                delete pAlien;
                delete this;
            }
            else
            {
                // else, we lose points
                emit sigDecreaseScore();
                scene()->removeItem(this);
                delete this;
            }
            return;
        }
    }

    // change the position of the bullet
    setPos(x(), y() - 10);
    // removing it if it goes too far
    if(pos().y()<0)
    {
        scene()-> removeItem(this);
        delete this;
    }
}

/**********************************************************************/


CPoints::CPoints(QGraphicsItem *pParent):QGraphicsTextItem(pParent)
{
    setPlainText(QString("Health = ") + QString::number(m_nHealth) + "\n"
                 + QString("Score : ") + QString::number(m_nScore));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));

}

void CPoints::increaseScore()
{
    m_nScore+=50;
    setPlainText(QString("Health = ") + QString::number(m_nHealth) + "\n"
                 + QString("Score : ") + QString::number(m_nScore));
}

void CPoints::decreaseScore()
{
    m_nScore-=50;
    setPlainText(QString("Health = ") + QString::number(m_nHealth) + "\n"
                 + QString("Score : ") + QString::number(m_nScore));
}

void CPoints::decreaseHealth()
{
    m_nScore--;
    setPlainText(QString("Health = ") + QString::number(m_nHealth) + "\n"
                 + QString("Score : ") + QString::number(m_nScore));
}

int CPoints::getHealth() const
{
    return m_nHealth;
}

int CPoints::getScore() const
{
    return m_nScore;
}

void CPoints::reset()
{
    m_nHealth = gMaxHealth;
    m_nScore = 50;
    setPlainText(QString("Health = ") + QString::number(m_nHealth) + "\n"
                 + QString("Score : ") + QString::number(m_nScore));

}


