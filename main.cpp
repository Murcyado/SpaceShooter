#include <QCoreApplication>
#include <QScreen>
#include <QApplication>

#include "spaceshooter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CSpaceShooter* pGame = new CSpaceShooter(qApp->screens()[0]->size());
    pGame->showFullScreen();
    pGame->Run();

    return a.exec();
}
