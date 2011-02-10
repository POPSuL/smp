#include "playlistmanager.h"

QMutex PlaylistManager::mutex;
PlaylistManager * PlaylistManager::instance = NULL;

PlaylistManager::PlaylistManager(QObject *parent) :
    QObject(parent)
{
    this->playlists = new QList<Playlist*>();
}

PlaylistManager * PlaylistManager::getInstance() {
    mutex.lock();
    if(instance == NULL)
        instance = new PlaylistManager();
    mutex.unlock();
    return instance;
}

QList<Playlist *> * PlaylistManager::getPlaylists() {
    return this->playlists;
}

Playlist * PlaylistManager::getPlaylistByIndex(uint index) {
    if(index < this->playlists.length()) {
        return this->playlists.at(index);
    }
    return NULL;
}
