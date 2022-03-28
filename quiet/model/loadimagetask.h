#ifndef LOADIMAGETASK_H
#define LOADIMAGETASK_H

#include <QObject>
#include <QRunnable>
#include <memory>

#include "object/image.h"


class LoadImageTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    LoadImageTask(QString& path);

    void run() override;

private:
    QString _path;

signals:
    void loadDone(std::shared_ptr<Image>, QString);


public slots:

};

#endif // LOADIMAGETASK_H
