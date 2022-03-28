#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QHash>
#include <QThreadPool>
#include <memory>

#include "object/image.h"
#include "model/loadimagetask.h"


class ImageManager : public QObject
{
    Q_OBJECT
public:
    explicit ImageManager(QObject *parent = 0);

    std::shared_ptr<Image> load(QString &path);

    void asyncLoad(QString &path, int priority);

private:
    QThreadPool* _pool;
    QHash<QString, LoadImageTask*> _tasks;

signals:
    void loadDone(std::shared_ptr<Image> image, const QString &path);


private slots:
    void onLoadDoneObserved(std::shared_ptr<Image> image, const QString &path);
};

#endif // IMAGEMANAGER_H
