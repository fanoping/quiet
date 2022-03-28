#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <memory>


class Image
{
public:
    Image(QString& path);
    ~Image();

    // getters
    std::shared_ptr<QImage> getImage() { return isEdited() ? _imageEdited :  _image; }
    std::shared_ptr<QImage> getSourceImage() { return _image; }

    // boolean
    bool isLoaded() { return _isLoaded; }
    bool isEdited() { return _isEdited; }

    // Image statistics
    int height() { return isEdited() ? _imageEdited->height() : _image->height(); }
    int width() { return isEdited() ? _imageEdited->width() : _image->width(); }
    QSize size() { return isEdited() ? _imageEdited->size() : _image->size(); }


signals:

public slots:

private:

    std::shared_ptr<QImage> _image;
    std::shared_ptr<QImage> _imageEdited;

    bool _isLoaded;
    bool _isEdited;

    // load method
    void load(QString& path);

};

#endif // IMAGE_H
