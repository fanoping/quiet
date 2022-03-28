#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>
#include <QDebug>
#include <QMap>



class ActionManager : public QObject
{
    Q_OBJECT
public:
    static ActionManager* getInstance();

    ~ActionManager();

private:
    explicit ActionManager(QObject *parent = 0);
    QMap<QString, QString> _shortcuts;  // <shortcut, action>

    // initialization
    static void initActions();



signals:
    void open();
    void close();

public slots:
    bool invokeAction(const QString &actionName);
};




extern ActionManager* actionManager;

#endif // ACTIONMANAGER_H
