#include "image.h"


Image::Image(QString &path) : _isLoaded(false), _isEdited(false)
{
    load(path);
}

Image::~Image()
{

}

void Image::load(QString& path)
{
    // Load Image


    _isLoaded = true;
}
