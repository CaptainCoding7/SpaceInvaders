#include "mainwindow.h"
#include <QScreen>
#include <QApplication>

#include "spaceinvaders.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    // we create an instance of the game
    CspaceInvaders *pGame = new CspaceInvaders(qApp->screens()[0]->size());
    // display it
    pGame->showFullScreen();
    // run it
    pGame->run();

    return a.exec();
}
