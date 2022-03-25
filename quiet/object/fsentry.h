#ifndef FSENTRY_H
#define FSENTRY_H

#include <QObject>

class FSEntry
{
public:
    FSEntry();
    void setPath();

private:
    QString basename;
    QString path;
    bool _isDirectory;

};

#endif // FSENTRY_H
