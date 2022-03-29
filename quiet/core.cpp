#include "core.h"

Core::Core() : QObject()
{
    initUI();
    initConnect();
}

/*

  Public

*/

void Core::show()
{
    if(mw){
        mw->show();
    }
}

/*

  Private

*/

void Core::initUI()
{
    mw = new MainWindow();
}

void Core::initConnect()
{
//    connect(mw, &MainWindow::onOpenAction, actionManager, &ActionManager::actionReceived);
    connect(actionManager, &ActionManager::openActionPublished, mw, &MainWindow::showOpenDialog);

//    connect(mw, &MainWindow::onOpenSelectedAction, actionManager, &ActionManager::actionReceived);
}
