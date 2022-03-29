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

    QAction* getAction(const QString& actionName) { return _actions[actionName]; }

private:
    explicit ActionManager(QObject *parent = 0);
    QMap<QString, QAction*> _actions;   // <actionName, actions>
    QMap<QString, QString> _shortcuts;  // <actionName, shortcut>


    // initialization
    static void initActions();
    static void initShortCuts();



signals:
    void open();
    void close();

    void openActionPublished();


public slots:
    bool actionReceived(const QString &actionName);
//    bool actionReceived(const QString &actionName, const QString& fileName);

private slots:
    void openActionReceived();
    void fileSelectedReceived();

};




extern ActionManager* actionManager;

#endif // ACTIONMANAGER_H
