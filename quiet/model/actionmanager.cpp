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
    }
    qDebug() << "Action Manager created";
    return actionManager;
}

// private
void ActionManager::initActions()
{
    actionManager->_shortcuts.insert("Ctrl+O", "open");

}

bool ActionManager::invokeAction(const QString &actionName)
{

    bool invoke  = QMetaObject::invokeMethod(this, actionName.toLatin1().constData(), Qt::DirectConnection);
    qDebug() << actionName.toLatin1().constData();
    qDebug() << invoke;
    return true;
}
