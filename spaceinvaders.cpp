#include "spaceinvaders.h"



CspaceInvaders::CspaceInvaders(QSize oScreenSize, QWidget *pParent):
    QGraphicsView(pParent),
    m_oScreenSize(oScreenSize)
{
    // creating the scene
    QGraphicsScene *pScene = new QGraphicsScene();
    setScene((pScene));
    pScene->setSceneRect(0, 0,  m_oScreenSize.width(), m_oScreenSize.height());

    setBackgroundBrush((QBrush(QImage(":/Ressources/SpaceInvadersBg.jpg"))));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");
}

void CspaceInvaders::run()
{
    scene()->clear();
    setCursor(Qt::BlankCursor);

    // creating the cannon
    m_pCannon = new CCannon(EColor::Red);
    m_pCannon->setPos(m_oScreenSize.width()/2, m_oScreenSize.height()-gCannonSize.height());
    m_pCannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_pCannon->setFocus();
    scene()->addItem(m_pCannon);

    connect(m_pCannon, &CCannon::sigIncreaseScore, this, &CspaceInvaders::onIncreaseScore);
    connect(m_pCannon, &CCannon::sigDecreaseScore, this, &CspaceInvaders::onDecreaseScore);

    // adding the points display
    m_pPoints = new CPoints();
    scene()->addItem(m_pPoints);

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &CspaceInvaders::onCreateEnemy);

}

void CspaceInvaders::checkPoints()
{
    // we check if the lose conditions are met
    if((m_pPoints->getScore() < 0) || (m_pPoints->getHealth() <= 0))
    {
        m_pPoints->reset();
        onGameOver();
    }
}

/*
 * Managing the key events
 */
void CspaceInvaders::keyPressEvent(QKeyEvent *pEvent)
{
    if(m_pCannon == nullptr)
        return;
    switch (pEvent->key())
    {
        case Qt::Key_Left:
        {
            if(m_pCannon->pos().x()>0)
                m_pCannon->setPos(m_pCannon->x() - 20, m_pCannon->y());
            break;
        }
        case Qt::Key_Right:
        {
        // we have to check that the cannon doesn't cross the right border
            if(m_pCannon->pos().x() + gCannonSize.width() < m_oScreenSize.width())
                m_pCannon->setPos(m_pCannon->x() + 20, m_pCannon->y());
            break;
        }
        // if we press the Z key, the color is changed
        case Qt::Key_Z:
        {
            int nColor = static_cast<int>(m_pCannon->getColor());
            m_pCannon->setColor(static_cast<EColor>(++nColor));
            break;
        }
        case Qt::Key_Space:
        {
            m_pCannon->shoot();
            break;
        }
    }
}

void CspaceInvaders::onCreateEnemy()
{
    // we generate an alien with a random X position and a random color
    int nPosX = 100 + (rand() % m_oScreenSize.width() - 100);
    int nColor = rand() % 3;

    CAlien *pAlien = new CAlien(static_cast<EColor>(nColor));
    pAlien->setPos(nPosX,0);

    scene()->addItem(pAlien);

    connect(pAlien, &CAlien::sigGameOver, this, &CspaceInvaders::onGameOver);
    connect(pAlien, &CAlien::sigDecreaseHealth, this, &CspaceInvaders::onDecreaseHealth);

}

void CspaceInvaders::onIncreaseScore()
{

}

void CspaceInvaders::onDecreaseScore()
{

}

void CspaceInvaders::onDecreaseHealth()
{

}

void CspaceInvaders::onGameOver()
{

}
