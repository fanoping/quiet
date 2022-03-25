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
    explicit DirectoryManager(QObject *parent = 0);
    ~DirectoryManager();

    bool setDirectory(QString dir);




signals:

    void dirLoaded();

public slots:


private:
    // Current Directory
    QString _directory;

    // Store loaded entryList (file / directory)
    // TODO: currently only first layer
    QList<FSEntry> fileEntryList;


    // load entry list from directory
    void loadEntryList(QString dir);
};

#endif // DIRECTORYMANAGER_H
