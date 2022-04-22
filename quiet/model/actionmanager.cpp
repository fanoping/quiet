#include "actionmanager.h"

ActionManager* g_actionManager = nullptr;

ActionManager::ActionManager(QObject *parent) : QObject(parent)
{

}

ActionManager::~ActionManager() {
}

ActionManager* ActionManager::getInstance()
{
    if (!g_actionManager) {
        g_actionManager = new ActionManager();
        initShortCuts();
    }
    return g_actionManager;
}

// private
void ActionManager::initShortCuts()
{
    g_actionManager->m_shortcuts.insert("Ctrl+O", "open");
}


// public slots

bool ActionManager::actionReceiver(const QAction* action)
{
    qDebug()<<action->text();
    bool invoked = QMetaObject::invokeMethod(this, (action->text().toLower()).toLatin1().constData(), Qt::DirectConnection);
    if(!invoked) {
        qDebug() << "[Debug] Action Manager" << action->text() << "invoked failed";
    }
    return invoked;
}
