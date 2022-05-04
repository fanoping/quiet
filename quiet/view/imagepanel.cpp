#include "imagepanel.h"


// TODO: - Resize event after zoom In/Out


ImagePanel::ImagePanel(QWidget *parent) : QGraphicsView(parent),
    m_scale(1.0),
    m_currViewportCenter(QPointF(0, 0))
{
    initLayout();
    initAttributes();
    initConnect();
    loadSettings();
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
    // Settings Changed
    connect(g_settingsManager, &Settings::settingsChanged, this, &ImagePanel::loadSettings);

    // zoom In/Out Menu Action
    connect(g_actionManager, &ActionManager::zoomIn, this, &ImagePanel::zoomInReceiver);
    connect(g_actionManager, &ActionManager::zoomOut, this, &ImagePanel::zoomOutReceiver);
}

void ImagePanel::initLayout()
{
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(-10000, -10000, 20000, 20000);
//    m_scene->setBackgroundBrush(g_settingsManager->themePalette().primaryBackground); ////// check if it can be removed
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
    centerOn(sceneRect().center());
}

void ImagePanel::zoomInReceiver()
{
    zoomIn(m_currViewportCenter);
}

void ImagePanel::zoomOutReceiver()
{
    zoomOut(m_currViewportCenter);
}

void ImagePanel::zoomIn(const QPointF& pos)
{
    m_scale = qMin(m_scale * 1.1, 4.0);
    m_pixmapItem.setScale(m_scale);

    m_currViewportCenter = pos;                 
    QGraphicsView::centerOn(pos);
}

void ImagePanel::zoomOut(const QPointF& pos)
{
    if(m_scale <= 1.0) return;
    m_scale = qMax(m_scale / 1.1, 1.0);
    m_pixmapItem.setScale(m_scale);

    m_currViewportCenter = pos;        
    QGraphicsView::centerOn(m_currViewportCenter);
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
        if (deltaY > 0) {
            zoomIn(mapToScene(event->pos()));
        } else if (deltaY < 0) {
            zoomOut(mapToScene(event->pos()));
        }
    } else {
        event->ignore();
    }
}

void ImagePanel::mousePressEvent(QMouseEvent* event)
{
    if(!m_pixmap) {
        QGraphicsView::mousePressEvent(event);
        return;
    }
    if(event->button() & Qt::LeftButton) {
        m_mouseMoveStartPos = event->pos();
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void ImagePanel::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton) {
        // Not working, wierd
        if(cursor().shape() != Qt::ClosedHandCursor) {
            setCursor(Qt::ClosedHandCursor);
        }

        m_mouseMoveStartPos -= event->pos();
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() + m_mouseMoveStartPos.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() + m_mouseMoveStartPos.y());

        m_mouseMoveStartPos = event->pos();
        m_currViewportCenter = mapToScene(viewport()->rect().center());
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


void ImagePanel::loadSettings()
{
    if(!m_scene) return;

    m_scene->setBackgroundBrush(g_settingsManager->themePalette().primaryBackground);
}


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

    m_currViewportCenter = QPointF(0, 0);
    QGraphicsView::centerOn(m_currViewportCenter);
}
