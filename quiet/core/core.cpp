#include "core.h"



Core::Core(int &argc, char **argv):
    QApplication(argc, argv)
{
    g_settingsManager = Settings::getInstance();

    g_actionManager = ActionManager::getInstance();
    g_directoryManager = DirectoryManager::getInstance();
    g_imageManager = ImageManager::getInstance();

    g_mainWindow = MainWindow::getInstance();
}

Core::~Core()
{

}


void Core::show()
{
    g_mainWindow->show();
}
