#include "playlist.h"

Playlist::Playlist(QObject *parent) :
    QObject(parent)
{
}

const QString& Playlist::getName() const {
    return this->name;
}

const QList<Track*>& Playlist::getTracks() const {
    return this->tracks;
}
