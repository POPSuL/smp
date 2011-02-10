#include "playlist.h"

Playlist::Playlist(QObject *parent) :
    QObject(parent)
{
}

QString Playlist::getName() {
    return this->name;
}

QList<Track*> * Playlist::getTracks() {
    return this->tracks;
}
