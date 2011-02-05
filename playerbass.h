#ifndef PLAYERBASS_H
#define PLAYERBASS_H
#include <QObject>
#include <QMutex>
#include "iMediaPlayer.h"
#include <bass/bass.h>
#include "global.h"

/**
  * Media player based on BASS library
  *
  * @author Viktor Suprun
  */
class PlayerBass : public iMediaPlayer
{
    Q_OBJECT
public:
    static iMediaPlayer * getInstance();
    virtual void play(QString file, bool withFade = false);
    virtual void pause();
    virtual void stop(bool withFadeOut = false);
    virtual bool isPlayed() const;
    virtual bool isPaused() const;
    virtual bool isStopped() const;
    virtual uint getCurrentPosition() const;
    virtual void setCurrentPosition(uint newPosition);
    virtual uint getDuration() const;
    virtual float getVolume() const;
    virtual void setVolume(float newVolume);
    virtual int getPan() const;
    virtual void setPan(int newPan);
    virtual QStringList * getSupportedExtensions() const;
    virtual bool isSupportedFile(QString fileName) const;
    virtual float * getFFTData(); //for visual
private:
    explicit PlayerBass(QObject *parent = 0);
    static QMutex mutex;
    static PlayerBass * instance;
signals:

public slots:

};

#endif // PLAYERBASS_H
