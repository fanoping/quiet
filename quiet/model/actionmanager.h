#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>
#include <QDebug>
#include <QMap>
#include <QAction>


class ActionManager : public QObject
{
    Q_OBJECT
public:
    static ActionManager* getInstance();
    ~ActionManager();

    QString getActionName(const QString& shortcut) { return m_shortcuts[shortcut]; }

private:
    explicit ActionManager(QObject *parent = 0);
    QMap<QString, QString> m_shortcuts;  // <shortcut, actionName>

    // initialization
    static void initShortCuts();

signals:
    // methodName = actionName (action.text() or a name mapping required)
    void open();


public slots:
    // Wrapper class to invoke corresponding signals
    // Make sure that always consistent to invoke the right method
    bool actionReceiver(const QAction* action);

};


extern ActionManager* g_actionManager;

#endif // ACTIONMANAGER_H
