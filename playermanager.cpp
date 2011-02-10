#include "playermanager.h"

QMutex PlayerManager::mutex;
PlayerManager * PlayerManager::instance = NULL;

PlayerManager::PlayerManager(QObject *parent) :
    QObject(parent)
{
#ifdef USEBASS
    this->player = PlayerBass::getInstance();
#endif
    //...
    if(this->player == NULL) {
        ERRM("Failed initialize player");
        exit(1);
    }
}

PlayerManager * PlayerManager::getInstance() {
    mutex.lock();
    if(instance == NULL)
        instance = new PlayerManager();
    mutex.unlock();
    return instance;
}

iMediaPlayer * PlayerManager::getPlayer() {
    return this->player;
}

