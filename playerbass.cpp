#include "playerbass.h"

QMutex PlayerBass::mutex;
PlayerBass * PlayerBass::instance = NULL;

PlayerBass::PlayerBass(QObject *parent)
{
    //ERRM("Error")
}

iMediaPlayer * PlayerBass::getInstance() {
    mutex.lock();
        if(instance == NULL)
            instance = new PlayerBass();
    mutex.unlock();
    return instance;
}

void PlayerBass::play(QString file, bool withFade) {
    //do it
}

void PlayerBass::pause() {
    //do it
}

void PlayerBass::stop(bool withFadeOut) {
    //do it
}

bool PlayerBass::isPaused() const {
    return false;
}

bool PlayerBass::isPlayed() const {
    return false;
}

bool PlayerBass::isStopped() const {
    return true;
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
    return 1.f;
}

void PlayerBass::setVolume(float newVolume) {

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
