#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QKeyEvent>

#include "settings.h"

enum class EColor
{
    Red, Pink, Blue
};

//class CBullet;
/*********************************************************************************/

class CBullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public :
    CBullet(EColor eColor, QGraphicsItem* pParent = nullptr);
    EColor getColor() const;
    void setColor(EColor eColor);


signals:
    void sigIncreaseScore();
    void sigDecreaseScore();

public slots:
    void onMove();

private:
    EColor m_eColor;

};

/***************************************************************/

/*
 * A class to manage the cannon
 */
class CCannon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    CCannon(EColor eColor, QGraphicsItem* pParent = nullptr);
    void shoot();
    EColor getColor() const;
    void setColor(EColor eColor);

signals:
    void sigIncreaseScore();
    void sigDecreaseScore();

private:
    EColor m_eColor;
};

/*******************************************************************/

class CAlien : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public :
    CAlien(EColor eColor, QGraphicsItem* pParent = nullptr);
    EColor getColor() const;
    void setColor(EColor eColor);

signals:
    void sigDecreaseHealth();
    void sigGameOver();

public slots:
    void onMove();

private:
    EColor m_eColor;

};

/******************************************************************************/

/*
 * A class to manage score and health
 */
class CPoints : public QGraphicsTextItem
{
public:
    CPoints(QGraphicsItem* pParent = nullptr);
    void increaseScore();
    void decreaseScore();
    void decreaseHealth();

    int getHealth() const;
    int getScore() const;

    void reset();

private:
    int m_nHealth = gMaxHealth;
    int m_nScore = 0;

};



#endif // COMPONENTS_H
