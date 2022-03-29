#include "actionmanager.h"

ActionManager* actionManager = nullptr;

ActionManager::ActionManager(QObject *parent) : QObject(parent)
{

}

ActionManager::~ActionManager() {
    delete actionManager;
}

ActionManager* ActionManager::getInstance()
{
    if (!actionManager) {
        actionManager = new ActionManager();
        initActions();
        initShortCuts();
    }
    return actionManager;
}

// private
void ActionManager::initActions()
{
    QAction* openAction = new QAction(tr("Open"), 0);
    actionManager->_actions.insert("open", openAction);
}

void ActionManager::initShortCuts()
{
    actionManager->_shortcuts.insert("open", "Ctrl+O");
}


// signals
// action publisher




// public slots

bool ActionManager::actionReceived(const QString &actionName)
{
    // true: action invoked
    // false: invoke failed
    qDebug() << actionName;
    return QMetaObject::invokeMethod(this, (actionName + "Received").toLatin1().constData(), Qt::DirectConnection);

}

//bool ActionManager::actionReceived(const QString &actionName, const QString &fileName)
//{
//    // true: action invoked
//    // false: invoke failed
//    qDebug() << actionName <<"with filename" << fileName;
//    return QMetaObject::invokeMethod(this, (actionName + "Received").toLatin1().constData(), Qt::DirectConnection);

//}

// private slots

void ActionManager::openActionReceived()
{
    qDebug() <<"Open Action Received";
    emit openActionPublished();
}

void ActionManager::fileSelectedReceived()
{

}

