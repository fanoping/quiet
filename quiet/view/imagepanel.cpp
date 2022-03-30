#include "imagepanel.h"

ImagePanel::ImagePanel(QWidget *parent) : QWidget(parent)
{

}



/*

  Public Methods

*/

void ImagePanel::initConnect()
{
    // Connect Loaded Image and Image Display

}


/*

  Public Slots

*/

bool ImagePanel::showImage(std::shared_ptr<QPixmap> image)
{
    if(!image){
        qDebug() <<" No image";
    }

    m_pixmap = std::move(image);
    qDebug() <<" show iMage";
    m_pixmapItem.setPixmap(*m_pixmap);
    m_pixmapItem.setTransformationMode(Qt::SmoothTransformation);
    m_pixmapItem.show();
    qDebug() <<" show iMage";

    return true;
}
