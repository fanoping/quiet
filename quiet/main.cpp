#include <QApplication>
#include "core/core.h"

#include "mainwindow.h"
#include "model/imagemanager.h"
#include "model/actionmanager.h"
#include "model/directorymanager.h"
#include "settings.h"
#include "object/node.h"


int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);

    Core core(argc, argv);

    // initialize all instances (TODO - move initialization into qApplication(wrapper))
    // mainWindow should always in the last order (wait for all instances created)
    // make connections in mainwindow ( and all nested widgets (view))
//    g_settingsManager = Settings::getInstance();

//    g_actionManager = ActionManager::getInstance();
//    g_directoryManager = DirectoryManager::getInstance();
//    g_imageManager = ImageManager::getInstance();

//    g_mainWindow = MainWindow::getInstance();

    // debug

//    g_mainWindow->show();
//    g_mainWindow->close();
    core.show();

    return core.exec();
}
