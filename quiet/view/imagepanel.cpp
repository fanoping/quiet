#include "imagepanel.h"

ImagePanel::ImagePanel(QWidget *parent) : QGraphicsView(parent)
{
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(0, 0, 600, 600);
    m_scene->setBackgroundBrush(QColor(60, 60, 103));
    m_scene->addItem(&m_pixmapItem);

    this->setFrameShape(QFrame::NoFrame);
    this->setScene(m_scene);
}

ImagePanel::~ImagePanel()
{

}

/*

  Public Methods

*/

void ImagePanel::initConnect()
{
    // Connect Loaded Image and Image Display
    connect(g_imageManager, &ImageManager::imageLoaded, this, &ImagePanel::showImage);
}


/*

  Public Slots

*/

void ImagePanel::showImage(std::shared_ptr<Image> image)
{
    if(!image){
        qDebug() <<" No image";
    }

    m_pixmap = std::move(image.get()->getPixmap());
    qDebug() <<" show iMage";
    m_pixmapItem.setPixmap(*m_pixmap);
    m_pixmapItem.setTransformationMode(Qt::SmoothTransformation);
    m_pixmapItem.show();
    qDebug() <<" show iMage";

}
