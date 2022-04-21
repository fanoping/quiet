#include "imagepanel.h"

ImagePanel::ImagePanel(QWidget *parent) : QGraphicsView(parent),
    m_scale(1.0)
{
    initLayout();
    initAttributes();
    initConnect();
}

ImagePanel::~ImagePanel()
{
    delete m_scene;
}

void ImagePanel::initAttributes()
{
    // Scrollbar Policies
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Remove White Borders
    this->setFrameShape(QFrame::NoFrame);
}

void ImagePanel::initConnect()
{

}

void ImagePanel::initLayout()
{
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(-1000, -1000, 2000, 2000);
    m_scene->setBackgroundBrush(g_settingsManager->themePalette().primaryBackground);
    m_scene->addItem(&m_pixmapItem);

    m_pixmapItem.setScale(1.0f);
    m_pixmapItem.setTransformationMode(Qt::SmoothTransformation);

    this->setScene(m_scene);
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


void ImagePanel::zoom(qreal scaler, const QPoint &pos)
{
   qDebug() << m_scale;
   qDebug() << scaler;
   if(underMouse()) {
       scaler = qMax(scaler, 1.0);  // Move out scaling parameter
       if ( scaler != m_scale) {
           m_scale = scaler;
           m_pixmapItem.setScale(m_scale);

           QPointF scenePos = mapToScene(pos);
           QPointF move = mapFromScene(scenePos) - pos;
           qDebug() << "Move" << move;
//           centerOn(newCenter);
           horizontalScrollBar()->setValue(move.x() + horizontalScrollBar()->value());
           verticalScrollBar()->setValue(move.y() + verticalScrollBar()->value());
       }
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


    //
//    qDebug() << cursor().pos();
//    qDebug() << mapFromGlobal(cursor().pos());
//    qDebug() <<this->mapToGlobal(this->pos());
//    qDebug() <<event->pos();
//    qDebug() << m_pixmapItem.boundingRect().width();
//    qDebug() << m_pixmapItem.boundingRect().height();

//    qDebug() << mapToScene(event->pos());



    if( event->modifiers() & Qt::ShiftModifier){

    } else if ( event->modifiers() == Qt::ControlModifier) {
        event->accept();
        int deltaY = event->angleDelta().ry();
        qDebug() << deltaY;
        if (deltaY > 0) {
            zoom(m_scale * 1.1, event->pos());
        } else if (deltaY < 0) {
            zoom(m_scale / 1.1, event->pos());
        }

    } else {
        event->ignore();
        QGraphicsView::wheelEvent(event);
    }
}


/*

  Public Slots

*/

//void ImagePanel::loadImage(const QString& mainEntry, const QList<QString>& entryList)
//{
//    Q_UNUSED(entryList);
//    HashKey key = g_directoryManager->getHashKey(mainEntry);
//    showImage(key);
//}

void ImagePanel::loadImage(const QString& mainEntry)
{
    HashKey key = g_directoryManager->getHashKey(mainEntry);
    showImage(key);
}

void ImagePanel::showImage(HashKey key)
{
    // Reset UI
    reset();

    m_pixmap = (*g_imageManager)[key]->getPixmap();
    m_pixmapItem.setPixmap(*m_pixmap);

    // Center the image at pos (0, 0)
    m_pixmapItem.setOffset(-m_pixmap->width() / 2.0, -m_pixmap->height() / 2.0);
    m_pixmapItem.setTransformOriginPoint(m_pixmapItem.boundingRect().center());
    m_pixmapItem.setTransformationMode(Qt::SmoothTransformation);
    m_pixmapItem.show();

}



