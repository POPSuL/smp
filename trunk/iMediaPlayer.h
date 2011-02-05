#ifndef IMEDIAPLAYER_H
#define IMEDIAPLAYER_H

#include <QObject>


class iMediaPlayer : public QObject {
    Q_OBJECT

public:
    static iMediaPlayer * getInstance();
    virtual void play(QString file, bool withFade = false) = 0;
    virtual void pause() = 0;
    virtual void stop(bool withFadeOut = false) = 0;
    virtual bool isPlayed() = 0;
    virtual bool isPaused() = 0;
    virtual bool isStopped() = 0;
    virtual uint getCurrentPosition() = 0;
    virtual void setCurrentPosition(uint newPosition) = 0;
    virtual uint getDuration() = 0;
    virtual float getVolume() = 0;
    virtual void setVolume(float newVolume) = 0;
    virtual int getPan() = 0;
    virtual void setPan(int newPan) = 0;
    virtual QStringList * getSupportedExtension() = 0;
    virtual bool isSupportedFile(QString fileName) = 0;
    virtual float * getFFTData() = 0; //for visual
signals:
    void startPlaying(QString file);
    void paused();
    void stopped();
    void volumeChanged(float newVolume);
    void panChanged(int newPan);
    void positionChanged(uint newPosition);

};

#endif // IMEDIAPLAYER_H
