#include <QtCore/QCoreApplication>
#include <QDebug>
#include "global.h"
#include "iMediaPlayer.h"
#include "playerbass.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    iMediaPlayer *player = PlayerBass::getInstance();
    return a.exec();
}
