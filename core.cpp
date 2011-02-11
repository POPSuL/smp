#include "core.h"

Core::Core(int argc, char* argv[], QObject *parent) :
    QObject(parent) {
    this->argc = argc;
    this->agrv = argv;
    this->playerManager = PlayerManager::getInstance();
    this->pluginsManager = PluginsManager::getInstance();
    this->application = new QApplication(this->argc, this->argv);
    this->config = new QSettings(this->application->applicationDirPath()+"config.ini", QSettings::IniFormat);
}

Core::~Core(){
    delete this->playerManager;
    delete this->pluginsManager;
    delete this->guiManager;
    delete this->application;
    delete this->config;
}

Core Core::getInstance(int argc, char* argv[]){
    if (Core::instance == NULL)
        Core::instance = new Core(argc, argv[]);

    return Core::instance;
}

void Core::configure(){
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
    return this->application->exec();
}

Core* Core::loadPlayerManager(){
    //@todo: player manager configuration
    return this;
}

Core* Core::loadPlugins(){
    this->pluginsManager->loadPlugins();

    //@todo: plugins loading
    return this;
}

void Core::loadGUI(){
}
