#include <QApplication>
#include <QDebug>
#include "global.h"
#include "iMediaPlayer.h"
#include "playerbass.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    iMediaPlayer *player = PlayerBass::getInstance();
    player->play("F:/Music/qcgeu6x4w.mp3");
    player->setPan(0);
#ifdef DBG
    qDebug() << "duration:" << player->getDuration();
#endif
    return a.exec();
}
