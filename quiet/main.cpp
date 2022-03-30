#include <QApplication>

#include "core.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // initialize all instances
    g_mainWindow = MainWindow::getInstance();
    actionManager = ActionManager::getInstance();
    directoryManager = DirectoryManager::getInstance();

    g_mainWindow->initConnect();

    g_mainWindow->show();

    return a.exec();
}
