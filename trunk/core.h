#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "global.h"
#include "playermanager.h"

/**
  * The highest level class provides an interface to configure and load
  * the whole Simple Media Player application.
  *
  * @package Simple Media Player
  * @author Yan Ivanov
 */
class Core : public QObject
{
    Q_OBJECT
public:

    /**
      * Returns a single core instance.
      *
      * @return Core
     */
    static Core* getInstance();

    /**
      * Configures application: loads player manager, plugins, GUI, configuration manager.
      *
      * @param int argc
      * @param char* argv
      * @return void
     */
    void configure(int argc, char* argv[]);

    /**
      * Create new QApplication object and passes execution result to main function.
      *
      * @return int
     */
    int loadApplication();

private:
    explicit Core(QObject *parent = 0);

    /**
      *
      * @return Core
     */
    Core* loadPlayerManager();

    /**
      *
      * @return Core
     */
    Core* loadPlugins();

    /**
      *
      * @return void
     */
    void loadGUI();

    static Core* instance;
    PlayerManager* playerManager;
    PluginsManager* pluginsManager;
    GuiManager* guiManager;
    configManager* configManager;

    /**
      * @var int command line argument
     */
    int argc;

    /**
      * @var char* command line argument
     */
    char* argv[];

signals:

public slots:

};

#endif // CORE_H
