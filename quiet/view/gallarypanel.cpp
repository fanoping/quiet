#include "gallarypanel.h"

GallaryPanel::GallaryPanel(QWidget *parent) : QGraphicsView(parent)
{
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(-300, -1000, 600, 2000);
    m_scene->setBackgroundBrush(QColor(60, 60, 60));

    // Widget Settings
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    this->setScene(m_scene);

}

GallaryPanel::~GallaryPanel()
{

}


void GallaryPanel::initConnect()
{

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
    // emit requestLoad signal
    // check if loaded (dirManager)


}

