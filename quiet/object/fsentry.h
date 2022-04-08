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
        return m_path == otherEntry.path();
    }
    bool FSEntry::operator==(const QString& otherPath) const {
        return m_path == otherPath;
    }

    QString path() const { return m_path; }

private:
    // filepath info
    QString m_basename;
    QString m_path;
    bool m_isDirectory;


};

#endif // FSENTRY_H
