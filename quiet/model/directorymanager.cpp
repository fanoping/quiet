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

QString const & DirectoryManager::getDirectory() const
{
     return m_directory;
}

void DirectoryManager::setDirectory(const QString& dir)
{
    m_directory = dir;
    qDebug() << "[Debug] DirectoryManager.cpp - Set directory to" <<  m_directory;
}


void DirectoryManager::appendFile(const QString& fileBasename, const QFileInfo& fileInfo)
{
    uint8_t fileChar;
    Node* nodePtr = m_fileEntriesRoot;
    for(int strIndex=0; strIndex < fileBasename.length(); ++strIndex) {
        fileChar = fileBasename[strIndex].toLatin1();
        nodePtr = nodePtr->insertChild(fileChar);
    }

    nodePtr->setValid();
    nodePtr->setFileInfo(fileInfo);
}

void DirectoryManager::removeFile(const QString& fileBasename)
{

}

void DirectoryManager::reset()
{
    m_fileEntriesRoot->clear();
}

QFileInfo DirectoryManager::getFileInfo(const QString& fileBasename)
{
    Node* queryNode = searchNode(fileBasename);
    return queryNode->getFileInfo();
}

HashKey DirectoryManager::getHashKey(const QString &fileBasename)
{
    // Request Image
    // Step 1. Check if it is a valid path, get the node if it is valid
    // Step 2. check if it is loaded in cache
    // Step 2a. if it is in cache, do nothing
    // Step 2b. if it is not in cache, request ImageManager to load in cache
    // Step 3. return a HashKey to the View which requested for the image

    Node* queryNode = searchNode(fileBasename);
    HashKey key;

//    qDebug() << "load" << fileBasename;

    if(!queryNode->isCached()) {
        key = g_imageManager->loadImage(queryNode->getFileInfo());
        queryNode->setCached();
        queryNode->setHashKey(key);
    } else {
        key = queryNode->getHashKey();
    }

    return key;
}

bool DirectoryManager::isValid(const QString &fileBasename)
{
    Node* queryNode = searchNode(fileBasename);
    return queryNode->isValid();
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

QList<QString> DirectoryManager::loadEntryList(QString dir)
{
    qDebug() << "[Debug] DirectoryManager.cpp - m_fileEntryList cleared";
    QList<QString> fileList;
    // tree clear
    m_fileEntriesRoot->clear();

    QDir directory(m_directory);
    QStringList files = directory.entryList();
    foreach (QString filename, files) {
       // Ignore "." (hidden files)
       if(filename.startsWith(".")) continue;

       QString fullpath = dir + "/" + filename;
       QFileInfo fileInfo(fullpath);

       if (QFileInfo(fullpath).isDir()) {
           // Directory, currently skipped
       }
       else {
           // Tree insertion
           QString basename(fileInfo.baseName());
           appendFile(basename, fileInfo);

           // return a fileBasename list for further query usage
           fileList.append(basename);
       }
    }

    // Debug Usage
    printTree();

    return fileList;
}

Node* DirectoryManager::searchNode(const QString &fileBasename)
{
    Node* queryNode = nullptr;
    QString tmp(fileBasename);

     if(!m_fileEntriesRoot->search(tmp, queryNode)) {
         return nullptr;
     }
     return queryNode;
}

// public slots

void DirectoryManager::dirReceived(const QString &path)
{
    qDebug() << "[Debug] DirectoryManager.cpp - Selected path:" << path;

    setDirectory(QFileInfo(path).absolutePath());
    QList<QString> entryList = loadEntryList(m_directory);

    emit directoryInitialized(QFileInfo(path).baseName(), entryList);
}

