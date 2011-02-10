#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QList>
#include "global.h"
#include "track.h"

class Playlist : public QObject
{
Q_OBJECT
public:
    explicit Playlist(QObject *parent = 0);
    QString getName();
    QList<Track *> * getTracks();
private:
    QString name;
    QList<Track *> * tracks;
signals:

public slots:

};

#endif // PLAYLIST_H
