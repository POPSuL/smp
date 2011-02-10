#include <QApplication>
#include <QDebug>
#include "global.h"
#include "iMediaPlayer.h"
#include "playerbass.h"
#include "core.h"
int main(int argc, char *argv[]) {
    Core* core = Core::getInstance();
    core->configure(argc, argv);
    return core->loadApplication();
}
