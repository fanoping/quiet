#include <QApplication>

#include "mainwindow.h"
#include "model/imagemanager.h"
#include "object/node.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // initialize all instances (TODO - move initialization into qApplication(wrapper))
    // mainWindow should always in the last order (wait for all instances created)
    // make connections in mainwindow ( and all nested widgets (view))
    g_actionManager = ActionManager::getInstance();
    g_directoryManager = DirectoryManager::getInstance();
    g_imageManager = ImageManager::getInstance();

    g_mainWindow = MainWindow::getInstance();

    // debug

    Node* n = new Node();
    qDebug() << n->isValid();
    qDebug() << n->getHashKey();

    g_mainWindow->show();
//    g_mainWindow->close();

    return a.exec();
}
