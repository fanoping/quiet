#include "gallarypanel.h"

/*
 * TODO:
 * - remove settings parameters out and transfer to util/settings
 * - ensureVisible -> selection (not default 0) (testing)
 * - pass not only 1 image to imagePanel (currently only one)
 * - resize event
 * - wheel event (should scroll horizontally)
 */

GallaryPanel::GallaryPanel(QWidget *parent) :
    QGraphicsView(parent),
    m_gallaryItemSize(128),
    m_gallaryItemPaddingSize(4)
{
    initSettings();
    initLayout();
    initAttributes();
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
    this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    // ScrollBar Policies
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

    // Others
    this->setAttribute(Qt::WA_TranslucentBackground, false);
    this->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    this->setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
    this->setRenderHint(QPainter::Antialiasing, false);
    this->setRenderHint(QPainter::SmoothPixmapTransform, false);

    // Remove white borders around QGraphicsWidget
    this->setFrameShape(QFrame::NoFrame);

    // Size for gallaryItem (size + horizontal Scrollbar size)
    // qDebug() <<this->horizontalScrollBar()->height(); // 30
    this->setMinimumHeight(176 + 15);
}


void GallaryPanel::initConnect()
{
    connect(g_directoryManager, &DirectoryManager::directoryInitialized, this, &GallaryPanel::loadGallaryItems);

    // connect scrollbar indicator
    connect(this->horizontalScrollBar(), &QScrollBar::valueChanged, this, &GallaryPanel::loadVisibleThumbnails);
}

void GallaryPanel::initLayout()
{
    // Set Alignment to the topleft corner
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Scene Setups
    m_scene = new QGraphicsScene();
    m_scene->setBackgroundBrush(g_settingsManager->themePalette().secondaryBackground);
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


    for(int idx = start; idx <= end; idx++) {
        m_gallaryItems[idx]->setPos(idx * (m_gallaryItemSize + 6 * (m_gallaryItemPaddingSize)), 0);
    }
}

void GallaryPanel::updateSceneSize()
{
    int width = qMax((int)m_scene->itemsBoundingRect().width(), this->width());
    int height = qMax((int)m_scene->itemsBoundingRect().height(), this->height());

    m_scene->update(0, 0, width, height);
    QPointF center = mapToScene(viewport()->rect().center());
    QGraphicsView::centerOn(center.x(), 0);
}

void GallaryPanel::updateGallaryItemSelection(const QList<int>& selection)
{
    foreach (int pos, m_selectedPos) {
        m_gallaryItems[pos]->setSelected(false);
    }

    foreach (int pos, selection) {
        m_gallaryItems[pos]->setSelected(true);
    }
    m_selectedPos = selection;
}

bool GallaryPanel::validPosition(int pos)
{
    return pos >=0 && pos < m_gallaryItems.count();
}

void GallaryPanel::ensureItemVisible(int pos)
{
    if(!validPosition(pos)) return;
    ensureVisible(m_gallaryItems.at(pos)->sceneBoundingRect(), m_gallaryItemSize, 0);
}

// Private

GallaryItem* GallaryPanel::createGallaryItem(const QString& entryStr)
{
    GallaryItem* gallaryItem = new GallaryItem(entryStr);
    gallaryItem->setPaddingSize(m_gallaryItemPaddingSize);
    gallaryItem->setSize(m_gallaryItemSize);
    return gallaryItem;
}

void GallaryPanel::resetGallaryItems()
{
    for(int itemIndex = 0; itemIndex < m_gallaryItems.count(); ++itemIndex) {
        if(m_gallaryItems[itemIndex]) {
            delete m_gallaryItems[itemIndex];
        }
    }
    m_gallaryItems.clear();
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

}

void GallaryPanel::mousePressEvent(QMouseEvent *event)
{
    // Deal only with left and right mouse click
    if(event->button() != Qt::LeftButton && event->button() != Qt::RightButton) {
        event->ignore();
        return;
    }

    GallaryItem* item = dynamic_cast<GallaryItem*>(itemAt(event->pos()));

    // Check whether the mouse clicks on item's boundingRect
    if(item) {
        int index = m_gallaryItems.indexOf(item);

        QList<int> newPos = m_selectedPos;

        if(event->button() == Qt::LeftButton) {
            if(event->modifiers() & Qt::ControlModifier) {
                newPos.append(index);
            } else {
                newPos = QList<int>() << index;
            }
        } else {
            newPos = QList<int>() << index;
        }
        emit onSelectedItems(m_gallaryItems.at(index)->getStr());
        updateGallaryItemSelection(newPos);
    }

    QGraphicsView::mousePressEvent(event);
}

void GallaryPanel::wheelEvent(QWheelEvent *event)
{
    // this->horizontalScrollBar().wheelEvent(event);
    event->accept();
    int angleDelta = event->angleDelta().y();
    QPointF center = mapToScene(viewport()->rect().center());
    QGraphicsView::centerOn(center.x() - angleDelta, center.y());
}


void GallaryPanel::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    updateSceneSize();
    update();
}

// Public slots

void GallaryPanel::showEvent(QShowEvent *event)
{
    QGraphicsView::showEvent(event);
    loadVisibleThumbnails();
    updateSceneSize();
}

void GallaryPanel::loadGallaryItems(const QString & mainEntry, const QList<QString>& entryList)
{
    // clear previous load
    resetGallaryItems();

    // create thumbnails
    GallaryItem* gallaryItem;
    int selectPos = 0;
    QList<int> newPos = QList<int>();

    for(int entryIdx = 0; entryIdx < entryList.count(); ++entryIdx)  {
        if(entryList[entryIdx] == mainEntry) {
            selectPos = entryIdx;
            newPos.append(entryIdx);
        }

        gallaryItem = createGallaryItem(entryList[entryIdx]);
        m_gallaryItems.append(gallaryItem);
        m_scene->addItem(gallaryItem);
    }
    updateGallaryItemPositions();
    updateSceneSize();
    ensureItemVisible(selectPos);

    updateGallaryItemSelection(newPos);
    emit onSelectedItems(mainEntry);
}
