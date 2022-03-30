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
    void open();
    void close();

    void openActionPublished();


public slots:
    bool actionReceived(const QString &actionName);


private slots:
    void openActionReceived();
    void fileSelectedReceived();

};




extern ActionManager* actionManager;

#endif // ACTIONMANAGER_H
