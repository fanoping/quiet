#include "core.h"



Core::Core(int &argc, char **argv):
    QApplication(argc, argv)
{

    // Setup Application App Name / Version
    QCoreApplication::setApplicationName("QUIET");
    QCoreApplication::setApplicationVersion(appVersion.toString());

    // Setup Application
    g_settingsManager = Settings::getInstance();

    g_actionManager = ActionManager::getInstance();
    g_directoryManager = DirectoryManager::getInstance();
    g_imageManager = ImageManager::getInstance();

    g_mainWindow = MainWindow::getInstance();

    qApp->processEvents();
}

Core::~Core()
{

}


void Core::show()
{
    g_mainWindow->show();
}
