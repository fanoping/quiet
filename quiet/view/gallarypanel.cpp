#include "gallarypanel.h"

/*
 * TODO:
 * - remove settings parameters out and transfer to util/settings
 * - ensureVisible -> selection (not default 0)
 */

GallaryPanel::GallaryPanel(QWidget *parent) :
    QGraphicsView(parent),
    m_gallaryItemSize(256),
    m_gallaryItemPaddingSize(4)
{
    initSettings();
    initLayout();
    initAttributes();
    m_scrollBar = this->horizontalScrollBar();
    initConnect();
}

GallaryPanel::~GallaryPanel()
{
    for(int itemIndex = 0; itemIndex < m_gallaryItems.count(); ++itemIndex) {
        if(m_gallaryItems[itemIndex]) {
            delete m_gallaryItems[itemIndex];
        }
    }
    delete m_scene;
}

void GallaryPanel::initAttributes()
{
    // Disable mouse propagation to parent
    this->setAttribute(Qt::WA_NoMousePropagation, true);

    // Receives mouse move events even if no buttons are pressed.
    this->setMouseTracking(true);

    // Keyboard Focus (default disable)
    this->setFocusPolicy(Qt::NoFocus);

    // attempt to find optimal method for updating viewport
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // ScrollBar Policies
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

    this->setAttribute(Qt::WA_TranslucentBackground, false);
    this->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    this->setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
    setRenderHint(QPainter::Antialiasing, false);
    setRenderHint(QPainter::SmoothPixmapTransform, false);
}


void GallaryPanel::initConnect()
{
    connect(g_directoryManager, &DirectoryManager::directoryInitialized, this, &GallaryPanel::loadThumbnails);

    // connect scrollbar indicator
    connect(m_scrollBar, &QScrollBar::valueChanged, this, &GallaryPanel::loadVisibleThumbnails);
}

void GallaryPanel::initLayout()
{
    // Set Alignment to the topleft corner
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Scene Setups
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(0, 0, 1000, 600);
    m_scene->setBackgroundBrush(QColor(60, 60, 60));
    this->setScene(m_scene);
}

void GallaryPanel::initSettings()
{

}

void GallaryPanel::updateGallaryItemPositions()
{
    updateGallaryItemPositions(0, m_gallaryItems.count() - 1);
}

void GallaryPanel::updateGallaryItemPositions(int start, int end)
{
    if(start > end) return;
    if(!validPosition(start) || !validPosition(end)) return;
    if(m_gallaryItems.empty()) return;


    for(int idx = start; idx <= end; idx++){
        m_gallaryItems[idx]->setPos(idx * (m_gallaryItemSize + 4 * m_gallaryItemPaddingSize) + m_gallaryItemPaddingSize, m_gallaryItemPaddingSize);
    }
}

void GallaryPanel::updateSceneSize()
{
    int width = qMax((int)m_scene->itemsBoundingRect().width(), this->width());
    int height = qMax((int)m_scene->itemsBoundingRect().height(), this->height());
    qDebug() << "Scene Size" << width <<  height;
    m_scene->setSceneRect(0, 0, width, height);
    QPointF center = mapToScene(viewport()->rect().center());
    QGraphicsView::centerOn(center.x(), 0);
}

bool GallaryPanel::validPosition(int pos)
{
    return pos >=0 && pos < m_gallaryItems.count();
}

void GallaryPanel::ensureItemVisible(int pos)
{
    if(!validPosition(pos)) return;
    ensureVisible(m_gallaryItems.at(pos), m_gallaryItemSize, 0);
}

// Private

GallaryItem* GallaryPanel::createGallaryItem(const QString& entryStr)
{
    GallaryItem* gallaryItem = new GallaryItem(entryStr);
    gallaryItem->setSize(m_gallaryItemSize);
    gallaryItem->setPaddingSize(m_gallaryItemPaddingSize);
    return gallaryItem;
}

void GallaryPanel::loadVisibleThumbnails()
{
    // Horizontal Orientation
    QRectF visibleRect = mapToScene(viewport()->geometry()).boundingRect();
    QRectF prevOffsetRect = QRectF(visibleRect.left() - offsetPreloadRange, visibleRect.top(),
                                                                       offsetPreloadRange, visibleRect.height());
    QRectF postOffsetRect = QRectF(visibleRect.left(), visibleRect.bottom(),
                                                                       offsetPreloadRange, visibleRect.height());

    // Only create visible items
    QList<QGraphicsItem*> visibleItems;

    if(previousScollDirection == SCROLL_INWARDS) {
         visibleItems = m_scene->items(visibleRect, Qt::IntersectsItemShape, Qt::AscendingOrder);
         // order: post > prev
         visibleItems.append(m_scene->items(postOffsetRect, Qt::IntersectsItemShape, Qt::AscendingOrder));
         visibleItems.append(m_scene->items(prevOffsetRect, Qt::IntersectsItemShape, Qt::DescendingOrder));
    } else {
        visibleItems = m_scene->items(visibleRect, Qt::IntersectsItemShape, Qt::DescendingOrder);
        // order: prev > post
        visibleItems.append(m_scene->items(prevOffsetRect, Qt::IntersectsItemShape, Qt::DescendingOrder));
        visibleItems.append(m_scene->items(postOffsetRect, Qt::IntersectsItemShape, Qt::AscendingOrder));
    }


    // Filter which visibleItem are not loaded in cache (ImageManager imgCache)
    // check if loaded (dirManager)
//    foreach (auto items, visibleItems) {
//        items->show();
//    }

}

// Public slots

void GallaryPanel::showEvent(QShowEvent *event)
{
    QGraphicsView::showEvent(event);
    loadVisibleThumbnails();
    updateSceneSize();
}

void GallaryPanel::loadThumbnails(const QString & mainEntry, const QList<QString>& entryList)
{
    Q_UNUSED(mainEntry);
    // create thumbnails
    GallaryItem* gallaryItem;
    for(int entryIdx = 0; entryIdx < entryList.count(); entryIdx++)  {
        gallaryItem = createGallaryItem(entryList[entryIdx]);
        m_gallaryItems.append(gallaryItem);
        m_scene->addItem(gallaryItem);
    }
    updateGallaryItemPositions();
    updateSceneSize();
    ensureItemVisible(0);
}
