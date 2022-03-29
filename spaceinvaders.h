#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>

#include <components.h>

class CspaceInvaders : public QGraphicsView
{
    Q_OBJECT
public:
    CspaceInvaders(QSize oScreenSize, QWidget* pParent = nullptr);

    void run();
    void checkPoints();

protected:
    void keyPressEvent(QKeyEvent *pEvent) override;

public slots :
    void onCreateEnemy();
    void onIncreaseScore();
    void onDecreaseScore();
    void onDecreaseHealth();
    void onGameOver();

private:
    CCannon *m_pCannon = nullptr;
    CPoints *m_pPoints = nullptr;
    QSize m_oScreenSize;

};

#endif // SPACEINVADERS_H
