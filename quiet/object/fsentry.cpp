#include "fsentry.h"

FSEntry::FSEntry()
{
}


FSEntry::FSEntry(const QString &path):
    m_path(path)
{
    QFileInfo fileInfo(path);

    if (fileInfo.isDir()) {
        qDebug() << "[Debug] FSEntry.cpp - directory constructed";
        m_basename = "";
        m_isDirectory = true;
    } else {
         QString basename(fileInfo.baseName());
         m_basename = basename;
         m_isDirectory = false;
    }
}



