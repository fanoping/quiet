#include "imagemanager.h"


ImageManager* g_imageManager = nullptr;

ImageManager::ImageManager(QObject *parent) : QObject(parent)
{
//    _pool = new QThreadPool(this);
}

ImageManager::~ImageManager()
{
    delete g_imageManager;
}

ImageManager* ImageManager::getInstance()
{
    if(!g_imageManager) {
        g_imageManager = new ImageManager();
    }
    return g_imageManager;
}



void ImageManager::load(QString &path)
{
    std::shared_ptr<Image> img = nullptr;
    img.reset(new Image(path));
    qDebug() << "img loaded" << path;
    emit imageLoaded(img);

}

//void ImageManager::asyncLoad(QString &path, int priority)
//{
//    if( _tasks.contains(path)) return;

//    auto runnableTask = new LoadImageTask(path);
//    runnableTask->setAutoDelete(false);
//    _tasks.insert(path, runnableTask);

//    connect(runnableTask, &LoadImageTask::loadDone, this, &ImageManager::onLoadDoneObserved, Qt::UniqueConnection);
//    _pool->start(runnableTask, priority);
//}


// signals and slots

//void ImageManager::onLoadDoneObserved(std::shared_ptr<Image> image, const QString &path)
//{
//    auto task = _tasks.take(path);
//    delete task;

//    emit loadDone(image, path);
//}


