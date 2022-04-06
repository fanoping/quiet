#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <memory>
#include <QPixmap>
#include <QDebug>


class Image
{
public:
    Image(QString& path);
    ~Image();

    // getters
    std::shared_ptr<QImage> getImage() { return isEdited() ? m_imageEdited :  m_image; }
    std::unique_ptr<QPixmap> getPixmap();
    std::shared_ptr<QImage> getSourceImage() { return m_image; }

    // boolean
    bool isLoaded() { return _isLoaded; }
    bool isEdited() { return _isEdited; }

    // Image statistics
    int height() { return isEdited() ? m_imageEdited->height() : m_image->height(); }
    int width() { return isEdited() ? m_imageEdited->width() : m_image->width(); }
    QSize size() { return isEdited() ? m_imageEdited->size() : m_image->size(); }


signals:

public slots:

private:

    std::shared_ptr<QImage> m_image;
    std::shared_ptr<QImage> m_imageEdited;

    bool _isLoaded;
    bool _isEdited;

    // load method
    void load(QString& path);

};

#endif // IMAGE_H