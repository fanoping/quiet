#include "imagepanel.h"

ImagePanel::ImagePanel(QWidget *parent) : QGraphicsView(parent),
    m_scale(1.0)
{

    // Graphics Scene Setup
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(-10000, -10000, 20000, 20000);
    m_scene->setBackgroundBrush(QColor(0, 0, 0));
    m_scene->addItem(&m_pixmapItem);

    qDebug()<< this->devicePixelRatio();
    // PixmapItem Setup
    m_pixmapItem.setScale(1.0f);
    m_pixmapItem.setTransformationMode(Qt::SmoothTransformation);
//    m_pixmapItem.setOffset(m_scene->width() / 2.0 - m_pixmap->get()->width(), m_scene->height() / 2.0 - m_pixmap->get()->height());

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
 * Private Methods
 */
void ImagePanel::reset()
{
    m_pixmapItem.setPixmap(QPixmap());
    m_pixmap.reset();
    m_scale = 1.0;
    centerOn(sceneRect().center());
}


void ImagePanel::zoomIn()
{
   qDebug() << m_scale;
   if(underMouse()) {
       m_scale = m_scale * 1.1;  // Move out scaling parameter
       m_pixmapItem.setScale(m_scale);

       QPointF c = m_pixmapItem.mapFromScene(mapToScene(mapFromGlobal(cursor().pos())));
       centerOn(c);
   }
}

void ImagePanel::zoomOut()
{
   qDebug() << m_scale;
   if(underMouse()) {
       m_scale = m_scale / 1.1;
       m_pixmapItem.setScale(m_scale);

       QPointF c = m_pixmapItem.mapFromScene(mapToScene(mapFromGlobal(cursor().pos())));
       centerOn(c);
   }
}


/*
   Mouse Events
*/

void ImagePanel::wheelEvent(QWheelEvent *event)
{
    if(!m_pixmap) {
        event->ignore();
        return;
    }
    /*
     * Reference
     * - pixelDelta: https://doc.qt.io/qt-5/qwheelevent.html#pixelDelta
     * - angleDelta: https://doc.qt.io/qt-5/qwheelevent.html#angleDelta
     *
     * ------------------------------------
     *  wheel:
     *           pixelDelta: (0, 0) ... always 0
     *           angleDelta: (0, +/-120) ... (outwards: +120, inwards: -120)
     * ------------------------------------
     */

    if( event->modifiers() & Qt::ShiftModifier){

    } else if ( event->modifiers() == Qt::ControlModifier) {
        event->accept();
        int deltaY = event->angleDelta().ry();
        qDebug() << deltaY;
        if (deltaY > 0) {
            zoomIn();
        } else if (deltaY < 0) {
            zoomOut();
        }

    } else {
        qDebug() << event->pixelDelta().rx();
        event->ignore();
        QGraphicsView::wheelEvent(event);

    }
}


/*

  Public Slots

*/

void ImagePanel::showImage(std::shared_ptr<Image> image)
{
    if(!image){
        qDebug() <<" No image";
    }

    reset();
    m_pixmap = std::move(image.get()->getPixmap());
    m_pixmapItem.setPixmap(*m_pixmap);
//    m_pixmapItem.setOffset(m_scene->width() / 2.0 - m_pixmap->width() / 2.0, m_scene->height() / 2.0 - m_pixmap->height() / 2.0);

    // Center the image at pos (0, 0)
    m_pixmapItem.setOffset(-m_pixmap->width() / 2.0, -m_pixmap->height() / 2.0);

    m_pixmapItem.show();

}


