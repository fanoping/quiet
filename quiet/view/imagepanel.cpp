#include "imagepanel.h"

ImagePanel::ImagePanel(QWidget *parent) : QGraphicsView(parent)
{

    // Graphics Scene Setup
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(0, 0, 20000, 20000);
    m_scene->setBackgroundBrush(QColor(60, 60, 103));
    m_scene->addItem(&m_pixmapItem);

    qDebug()<< this->devicePixelRatio();
    // PixmapItem Setup
    m_pixmapItem.setScale(1.0f);
    m_pixmapItem.setTransformationMode(Qt::SmoothTransformation);
//    m_pixmapItem.setOffset(m_scene->width() / 2.0 - m_pixmap->get()->width(), m_scene->height() / 2.0 - m_pixmap->get()->height());

    this->centerOn(&m_pixmapItem);

    // GraphicsView Setup
//    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
    m_pixmapItem.setOffset(m_scene->width() / 2.0 - m_pixmap->width() / 2.0, m_scene->height() / 2.0 - m_pixmap->height() / 2.0);
    m_pixmapItem.show();
    qDebug() <<" show iMage";

}
