#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>
#include <QDebug>
#include <QAction>
#include <QMap>
#include <QString>
#include <QKeySequence>

#include "object/action.h"


struct ActionAttributes {
    
    ActionAttributes() {}
    ~ActionAttributes() {}

    QString text;
    QKeySequence shortcut;
};


class ActionManager : public QObject
{
    Q_OBJECT
public:
    static ActionManager* getInstance();
    ~ActionManager();

    // Get action attributes, all QAction should be unique 
    // Cannot be shared with incorrect signals invoked
    bool cloneAction(const QString& name, ActionAttributes& attributes);

private:
    explicit ActionManager(QObject *parent = 0);

    // Action Attribution List
    QMap<QString, ActionAttributes> m_name2attributes;

    // initialize all available actions
    void initActionAttributes();

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
