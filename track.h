#ifndef TRACK_H
#define TRACK_H

#include <QObject>

/**
  * A track representation class.
  *
  * @package Simple Media Player
  * @author Viktor Suprun
  */
class Track : public QObject
{
Q_OBJECT
public:
    explicit Track(QObject *parent = 0);

signals:

public slots:

};

#endif // TRACK_H
