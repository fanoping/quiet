#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>
#include <QDebug>
#include <QAction>
#include <QMap>
#include <memory>

#include "object/action.h"


class ActionManager : public QObject
{
    Q_OBJECT
public:
    static ActionManager* getInstance();
    ~ActionManager();

    Action* cloneAction(const QString& name);

private:
    explicit ActionManager(QObject *parent = 0);
    QMap<QString, Action*> m_mapName2Action;

signals:
    // methodName = actionName (action.text() or a name mapping required)
    void open();


public slots:
    // Wrapper class to invoke corresponding signals
    // Make sure that always consistent to invoke the right method
    bool actionReceiver(QAction* action);

};


extern ActionManager* g_actionManager;

#endif // ACTIONMANAGER_H
