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

        initShortCuts();
    }
    return actionManager;
}

// private
void ActionManager::initShortCuts()
{
    actionManager->m_shortcuts.insert("Ctrl+O", "open");
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


// private slots

void ActionManager::openActionReceived()
{
    qDebug() <<"Open Action Received";
    emit openActionPublished();
}

void ActionManager::fileSelectedReceived()
{

}

