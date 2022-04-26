#include "actionmanager.h"

ActionManager* g_actionManager = nullptr;

ActionManager::ActionManager(QObject *parent) : QObject(parent)
{
    initActionAttributes();
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

bool ActionManager::cloneAction(const QString& name, ActionAttributes& attributes)
{
    if(!m_name2attributes.contains(name)) {
        return false;
    }

    attributes = m_name2attributes[name];
    return true;
}

bool ActionManager::actionReceiver(QAction* action)
{
    Action* receivedAction = dynamic_cast<Action*>(action);
    bool invoked = QMetaObject::invokeMethod(this, (receivedAction->name()).toLatin1().constData(), Qt::DirectConnection);
    if(!invoked) {
        qDebug() << "[Debug] Action Manager" << receivedAction->name() << "invoked failed";
    }
    return invoked;
}

void ActionManager::initActionAttributes()
{
    // open
    ActionAttributes openAttribute = ActionAttributes();
    openAttribute.text = "Open";
    openAttribute.shortcut = tr("Ctrl+O");
    m_name2attributes["open"] = openAttribute;
}