#include <QApplication>

#include "mainwindow.h"
#include "model/imagemanager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // initialize all instances (TODO - move initialization into qApplication(wrapper))
    g_mainWindow = MainWindow::getInstance();
    g_actionManager = ActionManager::getInstance();
    g_directoryManager = DirectoryManager::getInstance();
    g_imageManager = ImageManager::getInstance();

    g_mainWindow->initConnect();
    g_mainWindow->show();

    return a.exec();
}
