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

void PlayerBass::play(const QString& file, bool withFade) {
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
                       this->setPan(this->pan);
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
                       this->setPan(this->pan);
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
    if(this->bassInitialized) {
        QWORD pos = BASS_ChannelGetPosition(this->currentChannel, BASS_POS_BYTE);
        return (uint) BASS_ChannelBytes2Seconds(this->currentChannel, pos);
    } else {
        return 0;
    }
}

void PlayerBass::setCurrentPosition(uint newPosition) {
    QWORD pos = BASS_ChannelSeconds2Bytes(this->currentChannel, (double) newPosition);
    BASS_ChannelSetPosition(this->currentChannel, pos, BASS_POS_BYTE);
}

uint PlayerBass::getDuration() const {
    QWORD duration = BASS_ChannelGetLength(this->currentChannel, BASS_POS_BYTE);
    return (uint) BASS_ChannelBytes2Seconds(this->currentChannel, duration);
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
    return this->pan;
}

void PlayerBass::setPan(int newPan) {
    if(newPan > 100 || newPan < -100) {
        return;
    }
    this->pan = newPan;
    this->_setPan(this->currentChannel, this->pan);
}

const QStringList& PlayerBass::getSupportedExtensions() const {
    return 0;
}

bool PlayerBass::isSupportedFile(const QString& fileName) const {
    return false;
}

float * PlayerBass::getFFTData() {
    if(this->bassInitialized) {
        memset(this->fft, 0, sizeof(this->fft));
        BASS_ChannelGetData(this->currentChannel, fft, BASS_DATA_FFT8192);
        return fft;
    }
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

void PlayerBass::_setPan(DWORD channel, int newPan) {
    float pan;
    pan = newPan / 100.f;
    BASS_ChannelSetAttribute(channel, BASS_ATTRIB_PAN, pan);
}
