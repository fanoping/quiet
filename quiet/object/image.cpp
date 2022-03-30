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
    isEdited() ? pixmap->convertFromImage(*m_imageEdited) : pixmap->convertFromImage(*m_image, Qt::NoFormatConversion);
    return pixmap;
}

void Image::load(QString& path)
{
    // Load Image


    _isLoaded = true;
}
