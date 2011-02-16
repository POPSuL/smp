#include <QApplication>
#include <QDebug>
#include "global.h"
#include "iMediaPlayer.h"
#include "playerbass.h"
#include "core.h"
int main(int argc, char *argv[]) {
    Core* core = Core::getInstance(argc, argv);
    core->configure();
    return core->loadApplication();
}
