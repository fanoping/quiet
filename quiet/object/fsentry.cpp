#include "fsentry.h"

FSEntry::FSEntry()
{
}


FSEntry::FSEntry(const QString &path):
    _path(path)
{
    QFileInfo fileInfo(path);

    if (fileInfo.isDir()) {
        qDebug() << "[Debug] FSEntry.cpp - directory constructed";
         _basename = "";
         _isDirectory = true;
    } else {
         QString basename(fileInfo.baseName());
         _basename = basename;
         _isDirectory = false;
    }
}



