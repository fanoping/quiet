#ifndef DIRECTORYMANAGER_H
#define DIRECTORYMANAGER_H

#include <QObject>
#include <QDir>

// For debug usage
#include <QDebug>

#include "object/fsentry.h"
#include "object/node.h"
#include "imagemanager.h"
#include "util/utils.h"

class DirectoryManager : public QObject
{
    Q_OBJECT
public:
    static DirectoryManager* getInstance();

    ~DirectoryManager();

    QString getDirectory() { return m_directory; }
    bool setDirectory(QString dir);

    // Tree operators
    void insert(const QString queryStr);
    void remove(const QString queryStr);
    void reset();
    void printTree();  // for debugging

    QList<QString> query(const QString &queryStr=QString(""));


private:
    explicit DirectoryManager(QObject *parent = 0);
    // Current Directory
    QString m_directory;

    // Store loaded entryList (file / directory)
    // TODO: currently only first layer
    QList<FSEntry> m_fileEntryList;

    // load entry list from directory
    void loadEntryList(QString dir);

    // Tree Structure
    Node* m_fileEntriesRoot;


public slots:
    void dirReceived(const QString&);
};


extern DirectoryManager* g_directoryManager;

#endif // DIRECTORYMANAGER_H
