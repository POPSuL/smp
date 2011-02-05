#ifndef IMEDIAPLAYER_H
#define IMEDIAPLAYER_H

#include <QObject>

/**
  * This class is a generic player interface all players must implement
  *
  * @author Viktor Suprun
 */
class iMediaPlayer : public QObject {
    Q_OBJECT

public:
    /**
      * Provides a single instance of media player
      *
      * @return iMediaPlayer
     */
    static iMediaPlayer * getInstance();

    /**
      * Starts playing a track
      *
      * @param QString file being played
      * @param bool on true provide a fade in effect
      * @return void
     */
    virtual void play(QString file, bool withFadeIn = false) = 0;

    /**
      * Pauses playing and saves current position
      *
      * @return void
     */
    virtual void pause() = 0;

    /**
      * Stops playing and flushes current position
      *
      * @return void
     */
    virtual void stop(bool withFadeOut = false) = 0;

    /**
      *
      *
      * @return bool
     */
    virtual bool isPlayed() const = 0;

    /**
      * Indicates whether playing is paused
      *
      * @return bool
     */
    virtual bool isPaused() const = 0;

    /**
      * Indicates whether playing is stopped
      *
      * @return bool
     */
    virtual bool isStopped() const = 0;

    /**
      * Returns current position of playing track
      *
      * @return uint
     */
    virtual uint getCurrentPosition() const = 0;

    /**
      * Sets new current position within a track
      *
      * @param uint position within a track to set
      * @return void
     */
    virtual void setCurrentPosition(uint newPosition) = 0;

    /**
      * Returns track duration in seconds
      *
      * @return uint
     */
    virtual uint getDuration() const = 0;

    /**
      * Returns current player volume
      *
      * @return float
     */
    virtual float getVolume() const = 0;

    /**
      * Sets new player volume
      *
      * @param float new volume value
      * @return void
     */
    virtual void setVolume(float newVolume) = 0;

    /**
      * Returns current panorama position
      *
      * @return int panorama value; negative on left, positive on right
     */
    virtual int getPan() const = 0;

    /**
      * Sets new panorama position value
      *
      * @param int new panorama position value
      * @return void
     */
    virtual void setPan(int newPan) = 0;

    /**
      *
      *
      * @return QStringList
     */
    virtual QStringList * getSupportedExtensions() const = 0;

    /**
      *
      *
      * @param QString
      * @return bool
     */
    virtual bool isSupportedFile(QString fileName) const = 0;

    /**
      *
      *
      * @return float
     */
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
