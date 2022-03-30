#ifndef DIRECTORYMANAGER_H
#define DIRECTORYMANAGER_H

#include <QObject>
#include <QDir>

// For debug usage
#include <QDebug>

#include "object/fsentry.h"

class DirectoryManager : public QObject
{
    Q_OBJECT
public:
    static DirectoryManager* getInstance();

    ~DirectoryManager();

    bool setDirectory(QString dir);

private:
    explicit DirectoryManager(QObject *parent = 0);
    // Current Directory
    QString _directory;

    // Store loaded entryList (file / directory)
    // TODO: currently only first layer
    QList<FSEntry> _fileEntryList;


    // load entry list from directory
    void loadEntryList(QString dir);

public slots:
    void dirReceived(const QString&);
};


extern DirectoryManager* directoryManager;

#endif // DIRECTORYMANAGER_H
