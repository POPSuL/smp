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

Playlist * PlaylistManager::getPlaylistByName(QString name, bool ignoreCase) {
    if(name.isNull() || name.isEmpty()) {
        return NULL;
    }
    int len = this->playlists.length();
    for(int i = 0; i < len; i++) {
        Playlist * cplaylist = this->getPlaylistByIndex(i);
        Qt::CaseSensitivity cases = ignoreCase ? Qt::CaseInsensitive : Qt::CaseSensitive;
        if(cplaylist != NULL && cplaylist->getName().compare(name, cases)) {
            return cplaylist;
        }
    }
    return NULL;
}
