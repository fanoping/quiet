#include "imagemanager.h"

ImageManager::ImageManager(QObject *parent) : QObject(parent)
{
    _pool = new QThreadPool(this);
}


std::shared_ptr<Image> ImageManager::load(QString &path)
{
    std::shared_ptr<Image> img = nullptr;
    img.reset(new Image(path));

    return img;
}

void ImageManager::asyncLoad(QString &path, int priority)
{
    if( _tasks.contains(path)) return;

    auto runnableTask = new LoadImageTask(path);
    runnableTask->setAutoDelete(false);
    _tasks.insert(path, runnableTask);

    connect(runnableTask, &LoadImageTask::loadDone, this, &ImageManager::onLoadDoneObserved, Qt::UniqueConnection);
    _pool->start(runnableTask, priority);
}


// signals and slots

void ImageManager::onLoadDoneObserved(std::shared_ptr<Image> image, const QString &path)
{
    auto task = _tasks.take(path);
    delete task;

    emit loadDone(image, path);
}
