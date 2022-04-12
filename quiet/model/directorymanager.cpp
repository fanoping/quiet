#include "directorymanager.h"

//
// Constructor/Destructor
//

DirectoryManager* g_directoryManager = nullptr;

DirectoryManager::DirectoryManager(QObject *parent) : QObject(parent), m_directory("")
{
    // initialize a dummy root
    m_fileEntriesRoot = new Node();
}

DirectoryManager::~DirectoryManager()
{
    delete m_fileEntriesRoot;
    delete g_directoryManager;
}

DirectoryManager* DirectoryManager::getInstance()
{
    if (!g_directoryManager) {
        g_directoryManager = new DirectoryManager();
    }
    return g_directoryManager;
}

//
// Public Methods
//

bool DirectoryManager::setDirectory(QString path)
{
    if(path.isEmpty()) {
        qDebug() << "[Debug] DirectoryManager.cpp - Path is empty";
        return false;
    }

    m_directory = QFileInfo(path).absolutePath();
    loadEntryList(m_directory);

    qDebug() << g_imageManager;



    qDebug() << "[Debug] DirectoryManager.cpp - Directory" <<  m_directory << "loaded";
    return true;
}

/*
 * Tree operators
 */

void DirectoryManager::insert(const QString queryStr)
{

}

void DirectoryManager::remove(const QString queryStr)
{

}

void DirectoryManager::reset()
{
    m_fileEntriesRoot->clear();
}

QList<QString> DirectoryManager::query(const QString &queryStr)
{
   if(queryStr.isEmpty()) {
       return m_fileEntriesRoot->traverse();
   }
   // search before query
   Node* queryNode = nullptr;
   QString tmp(queryStr); // copy
   if(!m_fileEntriesRoot->search(tmp, queryNode)) {
        qDebug().noquote() << "Filename"  <<  queryStr << "not found";
       return QList<QString>();
   }

   QList<QString>queryResult = queryNode->traverse();
   if(queryNode->isValid()) {
       queryResult.append(queryStr);
   }
   for( int index=0; index< queryResult.count(); ++index) {
       queryResult[index] = queryStr + queryResult[index];
   }

   return queryResult;
}

void DirectoryManager::printTree()
{
   m_fileEntriesRoot->print();
}


// Private Methods

void DirectoryManager::loadEntryList(QString dir)
{
    qDebug() << "[Debug] DirectoryManager.cpp - m_fileEntryList cleared";
    m_fileEntryList.clear();

    // tree clear
    m_fileEntriesRoot->clear();

    QDir directory(m_directory);
    QStringList files = directory.entryList();
    foreach (QString filename, files) {
       // ignore "." (hidden files)
       if(filename.startsWith(".")) continue;

       QString fullpath = dir + "/" + filename;
       QFileInfo fileInfo(fullpath);

       if (QFileInfo(fullpath).isDir()) {
           // Directory, currently ignored
       }
       else {
           FSEntry newEntry(fullpath);
           m_fileEntryList.append(newEntry);

           // Tree
           QString basename(fileInfo.baseName());
           qDebug() << "basename" << basename;
           m_fileEntriesRoot->insert(basename);
       }
    }
    qDebug() << "[Debug] DirectoryManager.cpp - " << m_fileEntryList.length() << "files loaded";
    printTree();

    QList<QString> fileEntry = query(QString("gl"));
    foreach (QString item, fileEntry) {
        qDebug() <<item;
    }

}


// public slots

void DirectoryManager::dirReceived(const QString &path)
{
    qDebug() << "[Debug] DirectoryManager.cpp - Selected path:" << path;

    setDirectory(path);
    // load file
    g_imageManager->load(path);

}
