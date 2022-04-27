#include "imagepanel.h"


// TODO: - Resize event after zoom In/Out


ImagePanel::ImagePanel(QWidget *parent) : QGraphicsView(parent),
    m_scale(1.0),
    m_currViewportCenter(QPointF(0, 0))
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

    // Allow Drag Events
    this->setDragMode(QGraphicsView::ScrollHandDrag);
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


void ImagePanel::zoomIn(const QPoint& pos)
{
    if(underMouse()) {
        m_scale = m_scale * 1.1;
        m_pixmapItem.setScale(m_scale);
                
        m_currViewportCenter = mapToScene(pos);        
        QGraphicsView::centerOn(m_currViewportCenter);
    }
}

void ImagePanel::zoomOut(const QPoint& pos)
{
    if(m_scale <= 1.0) return;
    if(underMouse()) {
        m_scale = qMax(m_scale / 1.1, 1.0);
        m_pixmapItem.setScale(m_scale);

        m_currViewportCenter = mapToScene(pos);        
        QGraphicsView::centerOn(m_currViewportCenter);
    }
}

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
            zoomIn(event->pos());
        } else if (deltaY < 0) {
            zoomOut(event->pos());
        }

    } else {
        event->ignore();
    }
}

void ImagePanel::mouseReleaseEvent(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}

void ImagePanel::enterEvent(QEvent* event)
{
    QGraphicsView::enterEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}

void ImagePanel::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);
    QGraphicsView::centerOn(m_currViewportCenter);
}

/*

  Public Slots

*/

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
