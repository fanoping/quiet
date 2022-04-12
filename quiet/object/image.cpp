#include "image.h"


Image::Image(const QString &path) :  m_bIsLoaded(false), m_bIsEdited(false)
{
    load(path);
}

Image::~Image()
{

}

std::unique_ptr<QPixmap> Image::getPixmap()
{
    if(!isLoaded()) return nullptr;
    std::unique_ptr<QPixmap> pixmap(new QPixmap());
    qDebug()<< m_image.get();
    isEdited() ? pixmap->convertFromImage(*m_imageEdited) : pixmap->convertFromImage(*m_image.get(), Qt::NoFormatConversion);
    return pixmap;
}

void Image::load(const QString& path)
{
    // Load Image

    m_image.reset(new QImage(path));
    m_bIsLoaded = true;
}
