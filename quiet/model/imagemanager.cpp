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
    for(int cacheIndex=0; cacheIndex <m_cacheSize; ++cacheIndex){
        if(m_imageCache.get()[cacheIndex]) {
            delete m_imageCache.get()[cacheIndex];
        }
    }
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
    qDebug() << "load image" << fileInfo.absoluteFilePath();
    Image* img = new Image(fileInfo.absoluteFilePath());
    m_imageCache.get()[m_currHashKey] = img;
    return m_currHashKey++;
}

