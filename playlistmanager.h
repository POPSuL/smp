#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <QObject>
#include <QMutex>
#include <QList>
#include "global.h"
#include "playlist.h"

class PlaylistManager : public QObject
{
Q_OBJECT
public:
    static PlaylistManager * getInstance();
    QList<Playlist*> * getPlaylists();
    Playlist * getPlaylistByIndex(uint index);
    Playlist * getPlaylistByName(QString name, bool ignoreCase = true);

private:
    explicit PlaylistManager(QObject *parent = 0);
    static PlaylistManager * instance;
    static QMutex mutex;
    QList<Playlist *> playlists;

signals:

public slots:

};

#endif // PLAYLISTMANAGER_H
