#include "actionmanager.h"

ActionManager* g_actionManager = nullptr;

ActionManager::ActionManager(QObject *parent) : QObject(parent)
{

}

ActionManager::~ActionManager()
{

}

ActionManager* ActionManager::getInstance()
{
    if (!g_actionManager) {
        g_actionManager = new ActionManager();
    }
    return g_actionManager;
}

Action* ActionManager::cloneAction(const QString& name)
{
    if(m_mapName2Action.contains(name)) {
        return m_mapName2Action[name];
    } else {
        Action* action = new Action(name);
        m_mapName2Action[name] = action;
        return action;
    }
}

bool ActionManager::actionReceiver(QAction* action)
{
    Action* receivedAction = dynamic_cast<Action*>(action);
    bool invoked = QMetaObject::invokeMethod(this, (receivedAction->name().toLower()).toLatin1().constData(), Qt::DirectConnection);
    if(!invoked) {
        qDebug() << "[Debug] Action Manager" << action->text() << "invoked failed";
    }
    return invoked;
}
