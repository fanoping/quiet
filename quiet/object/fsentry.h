#ifndef FSENTRY_H
#define FSENTRY_H

#include <QObject>
#include <QFileInfo>
#include <QDebug>

class FSEntry
{
public:
    FSEntry();
    FSEntry(const QString& path);


    bool FSEntry::operator==(FSEntry& otherEntry) {
        return _path == otherEntry.path();
    }
    bool FSEntry::operator==(const QString& otherPath) const {
        return _path == otherPath;
    }

    QString path() const { return _path; }

private:
    QString _basename;
    QString _path;
    bool _isDirectory;

};

#endif // FSENTRY_H
