#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QHash>
#include <QThreadPool>
#include <memory>
#include <QDebug>

#include "object/image.h"




class ImageManager : public QObject
{
    Q_OBJECT
public:
    static ImageManager* getInstance();
    explicit ImageManager(QObject *parent = 0);
    ~ImageManager();


    void load(const QString &path);

    // TODO: asynchronous loading
//    void asyncLoad(QString &path, int priority);

private:
//    QThreadPool* _pool;
//    QHash<QString, LoadImageTask*> _tasks;

signals:
    void imageLoaded(std::shared_ptr<Image>);


private slots:

};

extern ImageManager* g_imageManager;

#endif // IMAGEMANAGER_H
