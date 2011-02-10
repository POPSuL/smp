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
  * @package Simple Media Player
  * @author Viktor Suprun
  */
class PlayerBass : public iMediaPlayer
{
    Q_OBJECT
public:
    static iMediaPlayer * getInstance();
    virtual void play(const QString& file, bool withFade = false);
    virtual void play();
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
    virtual const QStringList& getSupportedExtensions() const;
    virtual bool isSupportedFile(const QString& fileName) const;
    virtual float * getFFTData(); //for visual
private:
    explicit PlayerBass(QObject *parent = 0);
    static QMutex mutex;
    static PlayerBass * instance;

    void fadeIn(DWORD channel, float targetVolume);
    void fadeOut(DWORD channel);
    void e(DWORD c);
    void _setVolume(DWORD channel, float volume);
    void _setPan(DWORD channel, int pan);
    DWORD currentChannel;
    DWORD subChannel;
    QString currentFile;
    QString subfile;
    float volume;
    float fft[4096];
    int pan;
    bool bassInitialized;
signals:

public slots:

};

#endif // PLAYERBASS_H
