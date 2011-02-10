#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QObject>
#include <QMutex>
#include "global.h"
#include "iMediaPlayer.h"
#ifdef USEBASS
#include "playerbass.h"
#endif

class PlayerManager : public QObject
{
Q_OBJECT
public:
    static PlayerManager * getInstance();
    iMediaPlayer * getPlayer();
private:
    explicit PlayerManager(QObject *parent = 0);
    static PlayerManager * instance;
    static QMutex mutex;
    iMediaPlayer * player;

signals:

public slots:

};

#endif // PLAYERMANAGER_H
