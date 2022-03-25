#include "directorymanager.h"

//
// Constructor/Destructor
//

DirectoryManager::DirectoryManager(QObject *parent) : QObject(parent)
{

}

DirectoryManager::~DirectoryManager()
{

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

    emit dirLoaded();
    return true;
}

// Private Methods

void DirectoryManager::loadEntryList(QString dir)
{
    qDebug() << "[DirectoryManager.cpp] file entry list cleared";
    fileEntryList.clear();

    QDir directory(_directory);
    QStringList files = directory.entryList();
    foreach (QString filename, files) {
       // ignore "." (hidden files)
       if(filename.startsWith(".")) continue;

       qDebug() << filename;
       QString fullpath = dir + "/" + filename;
       if (QFileInfo(fullpath).isDir()) {
           qDebug() << "Dir";
       }
       else {
           qDebug() << "File";
       }

    }
}
