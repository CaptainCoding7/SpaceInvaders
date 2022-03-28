#include "mainwindow.h"
#include <QScreen>
#include <QApplication>

#include "spaceinvaders.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    CspaceInvaders *pGame = new CspaceInvaders(qApp->screens()[0]->size());
    pGame->showFullScreen();
    pGame->run();



    return a.exec();
}
