#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QHash>
#include <QThreadPool>
#include <memory>
#include <QDebug>

#include "object/image.h"
#include "util/utils.h"


class ImageManager : public QObject
{
    Q_OBJECT
public:
    static ImageManager* getInstance();
    explicit ImageManager(QObject *parent = 0);
    ~ImageManager();


    HashKey load(const QString &path);


private:
    // HashMap image caching
    int m_cacheSize;
    std::shared_ptr<Image*> m_imageCache;

    HashKey m_currHashKey;


signals:
    void imageLoaded(std::shared_ptr<Image>);


private slots:

};

extern ImageManager* g_imageManager;

#endif // IMAGEMANAGER_H
