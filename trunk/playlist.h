#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QList>
#include "global.h"
#include "track.h"

/**
  * A playlist representation class.
  *
  * @package Simple Media Player
  * @author Viktor Suprun
  */
class Playlist : public QObject
{
Q_OBJECT
public:
    explicit Playlist(QObject *parent = 0);
    const QString& getName() const;
    const QList<Track *>& getTracks() const;
private:
    QString name;
    QList<Track *> tracks;
signals:

public slots:

};

#endif // PLAYLIST_H
