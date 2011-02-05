#include "playerbass.h"

QMutex PlayerBass::mutex;
PlayerBass * PlayerBass::instance = NULL;

PlayerBass::PlayerBass(QObject *parent)
{
    ERRM("Error")
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

bool PlayerBass::isPaused() {
    return false;
}

bool PlayerBass::isPlayed() {
    return false;
}

bool PlayerBass::isStopped() {
    return true;
}

uint PlayerBass::getCurrentPosition() {
    return 0;
}

void PlayerBass::setCurrentPosition(uint newPosition) {
    //do it
}

uint PlayerBass::getDuration() {
    return 0;
}

float PlayerBass::getVolume() {
    return 1.f;
}

void PlayerBass::setVolume(float newVolume) {

}

int PlayerBass::getPan() {
    return 0;
}

void PlayerBass::setPan(int newPan) {
    //do it
}

QStringList * PlayerBass::getSupportedExtension() {
    return 0;
}

bool PlayerBass::isSupportedFile(QString fileName) {
    return false;
}

float * PlayerBass::getFFTData() {
    return NULL;
}
