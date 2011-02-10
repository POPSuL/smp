#include "core.h"

Core::Core(QObject *parent) :
    QObject(parent) {
}

Core Core::getInstance(){
    if (Core::instance == NULL)
        Core::instance = new Core();

    return Core::instance;
}

void Core::configure(int argc, char* argv[]){
    this->argc = argc;
    this->agrv = argv;

    try {
        this->loadPlayerManager()
            ->loadPlugins()
            ->loadGUI();
    }
    catch (Exception ex){
        //@todo: exception handling
    }
}

int Core::loadApplication(){
    QApplication app(this->argc, this->argv);
    return app.exec();
}

Core* Core::loadPlayerManager(){
    this->playerManager = PlayerManager::getInstance();
    //@todo: player manager configuration
    return this;
}

Core* Core::loadPlugins(){
    this->pluginsManager = PluginsManager::getInstance();
    this->pluginsManager->loadAll();
    return this;
}

void Core::loadGUI(){
}
