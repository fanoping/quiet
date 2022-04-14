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
    qDebug() << "[Debug] DirectoryManager.cpp - Set directory to" <<  m_directory;
    return true;
}

void DirectoryManager::insert(const QString& fileStr, const QFileInfo& fileInfo)
{
    uint8_t fileChar;
    Node* nodePtr = m_fileEntriesRoot;
    for(int strIndex=0; strIndex < fileStr.length(); ++strIndex) {
        fileChar = fileStr[strIndex].toLatin1();
        nodePtr = nodePtr->insertChild(fileChar);
    }

    nodePtr->setValid();
    nodePtr->setFileInfo(fileInfo);
}

void DirectoryManager::remove(const QString fileStr)
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

HashKey DirectoryManager::queryImage(const QString &queryImageStr)
{

    // Request Image
    // Step 1. Check if it is a valid path, get the node if it is valid
    // Step 2. check if it is loaded in cache
    // Step 2a. if it is in cache, do nothing
    // Step 2b. if it is not in cache, request ImageManager to load in cache
    // Step 3. return a HashKey to the View which requested for the image (single listener, no signal/slots)
    // Step 4. View retrieve the Image from HashList in ImageManager

    // Step 1
    Node* queryNode = isValid(queryImageStr);
    if(!queryNode) {
        return -1;
    }

    // Step 2
    if(!queryNode->isCached()) {

        HashKey key = g_imageManager->load(queryNode->getFileInfo().absoluteFilePath());
        qDebug() << "key" <<key;
        queryNode->setHashKey(key);
    }

    return queryNode->getHashKey();
}


Node* DirectoryManager::isValid(const QString &queryImageStr)
{

    Node* queryNode = nullptr;
    QString tmp(queryImageStr); // copy

     if(!m_fileEntriesRoot->search(tmp, queryNode)) {
         return nullptr;
     }
     return queryNode;
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
       // ignore "." (hidden files)
       if(filename.startsWith(".")) continue;

       QString fullpath = dir + "/" + filename;
       QFileInfo fileInfo(fullpath);

       if (QFileInfo(fullpath).isDir()) {
           // Directory, currently ignored
       }
       else {
           // Tree
           QString basename(fileInfo.baseName());
           fileList.append(basename);
           qDebug() << "basename" << fileList;
           insert(basename, fileInfo);
       }
    }

    printTree();

    return fileList;


}


// public slots

void DirectoryManager::dirReceived(const QString &path)
{
    qDebug() << "[Debug] DirectoryManager.cpp - Selected path:" << path;

    setDirectory(path);
    QList<QString> entryList = loadEntryList(m_directory);

    emit directoryInitialized(QFileInfo(path).baseName(), entryList);


    // load file
//    g_imageManager->load(path);

}
