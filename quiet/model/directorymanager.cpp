#include "directorymanager.h"

//
// Constructor/Destructor
//

DirectoryManager* directoryManager = nullptr;

DirectoryManager::DirectoryManager(QObject *parent) : QObject(parent)
{

}

DirectoryManager::~DirectoryManager()
{
    delete directoryManager;
}

DirectoryManager* DirectoryManager::getInstance()
{
    if (!directoryManager) {
        directoryManager = new DirectoryManager();
    }
    return directoryManager;
}

//
// Public Methods
//

bool DirectoryManager::setDirectory(QString dirname)
{
    if(dirname.isEmpty()) {
        qDebug() << "[Debug] DirectoryManager.cpp - Directory name is empty";
        return false;
    }
    if(!QDir(dirname).exists()){
        qDebug() << "[Debug] DirectoryManager.cpp - Directory name does not exists";
        return false;
    }

    _directory = dirname;
    loadEntryList(dirname);

    qDebug() << "[Debug] DirectoryManager.cpp - Directory" <<  dirname  << "loaded";

    return true;
}

// Private Methods

void DirectoryManager::loadEntryList(QString dir)
{
    qDebug() << "[DirectoryManager.cpp] file entry list cleared";
    _fileEntryList.clear();

    QDir directory(_directory);
    QStringList files = directory.entryList();
    foreach (QString filename, files) {
       // ignore "." (hidden files)
       if(filename.startsWith(".")) continue;

       QString fullpath = dir + "/" + filename;

       if (QFileInfo(fullpath).isDir()) {
           // Directory, currently ignored
       }
       else {
           FSEntry newEntry(fullpath);
           _fileEntryList.append(newEntry);

       }
    }
    qDebug() << "[Debug] DirectoryManager.cpp - " << _fileEntryList.length() << "files loaded";
}


// public slots

void DirectoryManager::dirReceived(const QString &)
{
    qDebug() <<"dirReceived";
}
