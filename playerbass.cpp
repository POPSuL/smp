#include "playerbass.h"
#include <QFile>

QMutex PlayerBass::mutex;
PlayerBass * PlayerBass::instance = NULL;

PlayerBass::PlayerBass(QObject *parent)
{
    this->bassInitialized = false;
    BOOL bassStatus = BASS_Init(-1, 44100, NULL, NULL, NULL);
    if(!bassStatus) {
        DWORD errorCode = BASS_ErrorGetCode();
        ERRM("Failed init BASS. Error code: " + errorCode);
        exit(0);
    }
    if(!BASS_SetConfig(BASS_CONFIG_FLOATDSP, true)) {
#ifdef DBG
        qDebug() << "failed set floatdsp. Error code:" << BASS_ErrorGetCode();
#endif
    }
    //...
    this->volume = 0.1f;
    this->bassInitialized = true;
}

iMediaPlayer * PlayerBass::getInstance() {
    mutex.lock();
        if(instance == NULL)
            instance = new PlayerBass();
    mutex.unlock();
    return instance;
}

void PlayerBass::play(QString file, bool withFade) {
#ifdef DBG
    qDebug() << "Start playing";
#endif
    if(this->bassInitialized) {
            QFile f(file);
            DWORD error;
            if(f.exists()) {
                if(withFade) {
                   this->e(this->subChannel);
                   this->subChannel = this->currentChannel;
                   this->currentChannel = BASS_StreamCreateFile(false, f.fileName().toLocal8Bit().constData(), 0, 0, BASS_STREAM_AUTOFREE);
                   error = BASS_ErrorGetCode();
                   if(this->currentChannel && error == BASS_OK) {
                       this->_setVolume(this->currentChannel, 0.f);
                       this->fadeIn(this->currentChannel, this->volume);
                       if(this->isPlayed())
                           this->fadeOut(this->subChannel);
                       else
                           this->e(this->subChannel);
                   } else {
                       this->currentChannel = this->subChannel;
                       this->subChannel = 0;
#ifdef DBG
                       qDebug() << "Error" << error;
#endif
                   }
               } else {
                   this->e(this->subChannel);
                   this->subChannel = this->currentChannel;
                   this->currentChannel = BASS_StreamCreateFile(false, f.fileName().toLocal8Bit().constData(), 0, 0, BASS_STREAM_AUTOFREE);
                   error = BASS_ErrorGetCode();
                   if(this->currentChannel && error == BASS_OK) {
                       this->setVolume(this->volume);
                       this->play();
                   } else {
                       this->currentChannel = this->subChannel;
                       this->subChannel = 0;
#ifdef DBG
                       qDebug() << "Error" << error;
#endif
                   }
               }
           } else {
               this->currentChannel = this->subChannel;
               this->subChannel = 0;
#ifdef DBG
               qDebug() << "File" << f.fileName() << "does't exists";
#endif
           }
    }
}

void PlayerBass::play() {
    if(this->currentChannel) {
        if(this->isPaused()) {
            BASS_ChannelPlay(this->currentChannel, false);
        } else {
            if(this->isStopped())
                BASS_ChannelPlay(this->currentChannel, true);
        }
    }
}

void PlayerBass::pause() {
    if(this->bassInitialized) {
        if(!BASS_ChannelPause(this->currentChannel)) {
#ifdef DBG
            qDebug() << "Pause error:" << BASS_ErrorGetCode();
#endif
        }
    }
}

void PlayerBass::stop(bool withFadeOut) {
    if(this->bassInitialized) {
        BASS_ChannelStop(this->currentChannel);
    }
}

bool PlayerBass::isPaused() const {
    return BASS_ChannelIsActive(this->currentChannel) == BASS_ACTIVE_PAUSED;
}

bool PlayerBass::isPlayed() const {
    return BASS_ChannelIsActive(this->currentChannel) == BASS_ACTIVE_PLAYING;
}

bool PlayerBass::isStopped() const {
    return BASS_ChannelIsActive(this->currentChannel) == BASS_ACTIVE_STOPPED ||
            BASS_ChannelIsActive(this->currentChannel == BASS_ACTIVE_STALLED);
}

uint PlayerBass::getCurrentPosition() const {
    return 0;
}

void PlayerBass::setCurrentPosition(uint newPosition) {
    //do it
}

uint PlayerBass::getDuration() const {
    return 0;
}

float PlayerBass::getVolume() const {
    return this->volume;
}

void PlayerBass::setVolume(float newVolume) {
    if(newVolume > 1.f || newVolume < 0.f)
        return;
    this->volume = newVolume;
    this->_setVolume(this->currentChannel, this->volume);
}

int PlayerBass::getPan() const {
    return 0;
}

void PlayerBass::setPan(int newPan) {
    //do it
}

QStringList * PlayerBass::getSupportedExtensions() const {
    return 0;
}

bool PlayerBass::isSupportedFile(QString fileName) const {
    return false;
}

float * PlayerBass::getFFTData() {
    return NULL;
}

void PlayerBass::fadeIn(DWORD channel, float targetVolume) {
    //do it!!!
    this->_setVolume(channel, targetVolume);
    BASS_ChannelPlay(channel, true);
}

void PlayerBass::fadeOut(DWORD channel) {
    //do it!!!
    BASS_ChannelStop(channel);
    this->e(channel);
}

void PlayerBass::e(DWORD c) {
    BASS_StreamFree(c);
}

void PlayerBass::_setVolume(DWORD channel, float volume) {
    BASS_ChannelSetAttribute(channel, BASS_ATTRIB_VOL, volume);
}
