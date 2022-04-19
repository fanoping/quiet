#ifndef DIRECTORYMANAGER_H
#define DIRECTORYMANAGER_H

#include <QObject>
#include <QDir>

// For debug usage
#include <QDebug>
#include <QMessageLogger>

#include "object/node.h"
#include "imagemanager.h"
#include "util/utils.h"

class DirectoryManager : public QObject
{
    Q_OBJECT
public:
    static DirectoryManager* getInstance();
    ~DirectoryManager();

    QString const & getDirectory() const;
    void setDirectory(const QString& dir);

    void appendFile(const QString& fileBasename, const QFileInfo& fileInfo);
    void removeFile(const QString& fileBasename); // TODO
    void reset();
    void printTree();  // for debugging

    QFileInfo getFileInfo(const QString& fileBasename);
    HashKey getHashKey(const QString& fileBasename);
    bool isValid(const QString &fileBasename);


    QList<QString> query(const QString &queryStr=QString(""));



private:
    explicit DirectoryManager(QObject *parent = 0);
    // Current Directory
    QString m_directory;

    // Store loaded entryList (file / directory)
    // TODO: currently only first layer

    // load entry list from directory
    QList<QString> loadEntryList(QString dir);

    // Tree Structure
    Node* m_fileEntriesRoot;
    Node* searchNode(const QString& fileBasename);



signals:
    void directoryInitialized(const QString&, const QList<QString>&);

public slots:
    // When mainWindow openfileDialog selected a file, it passes a filepath to this slot
    void dirReceived(const QString& path);
};


extern DirectoryManager* g_directoryManager;

#endif // DIRECTORYMANAGER_H
