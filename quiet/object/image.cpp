#include "image.h"


Image::Image(QString &path) : _isLoaded(false), _isEdited(false)
{
    load(path);
}

Image::~Image()
{

}

std::unique_ptr<QPixmap> Image::getPixmap()
{
    std::unique_ptr<QPixmap> pixmap(new QPixmap());
    qDebug()<< m_image.get();
    isEdited() ? pixmap->convertFromImage(*m_imageEdited) : pixmap->convertFromImage(*m_image.get(), Qt::NoFormatConversion);
    return pixmap;
}

void Image::load(QString& path)
{
    // Load Image

    m_image.reset(new QImage(path));
    _isLoaded = true;
}
