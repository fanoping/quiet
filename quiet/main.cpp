#include <QApplication>

#include "core.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // initialize all instances
    actionManager = ActionManager::getInstance();
    directoryManager = DirectoryManager::getInstance();

    Core core;

    core.show();

    return a.exec();
}
