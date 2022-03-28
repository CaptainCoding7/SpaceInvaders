#include "spaceinvaders.h"

CspaceInvaders::CspaceInvaders(QSize oScreenSize, QWidget *pParent):
    QGraphicsView(pParent),
    m_oScreenSize(oScreenSize)
{
    QGraphicsScene *pScene = new QGraphicsScene();
    setScene((pScene));

    pScene->setSceneRect(0, 0,  m_oScreenSize.width(), m_oScreenSize.height());

    setBackgroundBrush((QBrush(QImage(":/Ressources/SpaceIvadersBg.jpg"))));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");
}

void CspaceInvaders::run()
{
    scene()->clear();
    setCursor(Qt::BlankCursor);

    m_pCannon = new CCannon(EColor::Red);
    m_pCannon->setPos(m_oScreenSize.width()/2, m_oScreenSize.height()-gCannonSize.height());
    m_pCannon->setFlag(QGraphicsIte::ItemIsFocusable);
    m_pCannon->setFocus();
    scene()->addItem(m_pCannon);

    connect(m_pCannon, &CCannon::sigIncreaseScore, this, &CspaceInvader::onIncreaseScore());
    connect(m_pCannon, &CCannon::sigDecreaseScore, this, &CspaceInvader::onDecreaseScore());

    m_pPoints = new CPoints();
    scene()->addItem(m_pPoints);

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &CspaceInvaders::onCreateEnemy);

}

void CspaceInvaders::checkPoints()
{

}