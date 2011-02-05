#ifndef PLAYERBASS_H
#define PLAYERBASS_H
#include <QObject>
#include <QMutex>
#include "iMediaPlayer.h"
#include <bass/bass.h>
#include "global.h"

class PlayerBass : public iMediaPlayer
{
    Q_OBJECT
public:
    static iMediaPlayer * getInstance();
    virtual void play(QString file, bool withFade = false);
    virtual void pause();
    virtual void stop(bool withFadeOut = false);
    virtual bool isPlayed();
    virtual bool isPaused();
    virtual bool isStopped();
    virtual uint getCurrentPosition();
    virtual void setCurrentPosition(uint newPosition);
    virtual uint getDuration();
    virtual float getVolume();
    virtual void setVolume(float newVolume);
    virtual int getPan();
    virtual void setPan(int newPan);
    virtual QStringList * getSupportedExtension();
    virtual bool isSupportedFile(QString fileName);
    virtual float * getFFTData(); //for visual
private:
    explicit PlayerBass(QObject *parent = 0);
    static QMutex mutex;
    static PlayerBass * instance;
signals:

public slots:

};

#endif // PLAYERBASS_H
