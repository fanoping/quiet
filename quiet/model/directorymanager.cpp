#include "directorymanager.h"

//
// Constructor/Destructor
//

DirectoryManager* g_directoryManager = nullptr;

DirectoryManager::DirectoryManager(QObject *parent) : QObject(parent), m_directory("")
{
    // initialize a dummy root
    m_fileEntries = new FSEntry();
}

DirectoryManager::~DirectoryManager()
{
    delete m_fileEntries;
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
    // load file
    g_imageManager->load(path);


    qDebug() << "[Debug] DirectoryManager.cpp - Directory" <<  m_directory << "loaded";
    return true;
}

// Private Methods

void DirectoryManager::loadEntryList(QString dir)
{
    qDebug() << "[Debug] DirectoryManager.cpp - m_fileEntryList cleared";
    m_fileEntryList.clear();

    QDir directory(m_directory);
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
           m_fileEntryList.append(newEntry);
//           g_imageManager->load(fullpath);
       }
    }
    qDebug() << "[Debug] DirectoryManager.cpp - " << m_fileEntryList.length() << "files loaded";
}


// public slots

void DirectoryManager::dirReceived(const QString &path)
{
    qDebug() << "[Debug] DirectoryManager.cpp - Selected path:" << path;

    setDirectory(path);


}
