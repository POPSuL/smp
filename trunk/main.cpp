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
    return a.exec();
}
