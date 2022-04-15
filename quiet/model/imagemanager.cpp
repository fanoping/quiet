#include "imagemanager.h"


ImageManager* g_imageManager = nullptr;

ImageManager::ImageManager(QObject *parent) :
    QObject(parent),
    m_cacheSize(64),
    m_currHashKey(0)
{
    m_imageCache.reset(new Image*[m_cacheSize]);


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



HashKey ImageManager::load(const QString &path)
{
    std::shared_ptr<Image> img = nullptr;
    img.reset(new Image(path));
    qDebug() << "img loaded" << path;
    emit imageLoaded(img);
    return m_currHashKey++;
}

HashKey ImageManager::loadImage(const QFileInfo& fileInfo)
{

    return 0;
}

