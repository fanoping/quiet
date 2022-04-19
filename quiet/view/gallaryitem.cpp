#include "gallaryitem.h"

GallaryItem::GallaryItem(QGraphicsItem *parent):
    QGraphicsWidget(parent),
    m_entryStr(""),
    m_sizeX(100), m_sizeY(100),
    m_paddingTop(0), m_paddingBottom(0),
    m_paddingLeading(0), m_paddingTrailing(0)
{

}

GallaryItem::GallaryItem(const QString& entryStr, QGraphicsItem *parent):
    QGraphicsWidget(parent),
    m_entryStr(entryStr),
    m_sizeX(100), m_sizeY(100),
    m_paddingTop(0), m_paddingBottom(0),
    m_paddingLeading(0), m_paddingTrailing(0)
{

}

GallaryItem::~GallaryItem()
{

}


/*
 * Public
 */


void GallaryItem::size(qreal x, qreal y)
{
    if(x <= 0 || y <=0) {
        qDebug("[Debug] GallaryItem - Invalid item size (%d, %d)" , x , y);
        return;
    }

    m_sizeX = x;
    m_sizeY = y;

    updateBoundingRect();
}

void GallaryItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    HashKey key = g_directoryManager->getHashKey(m_entryStr);
    m_pixmap = (*g_imageManager)[key]->getPixmap();
    drawThumbnail(painter);
}



/*
 *  Private
 */

void GallaryItem::updateBoundingRect()
{
    m_boundingRect = QRectF(0, 0, m_sizeX, m_sizeY);
    m_boundingRect.adjust(-m_paddingLeading, -m_paddingTop, m_paddingTrailing, m_paddingBottom);
    m_boundingRect.moveTo(0, 0);
}


void GallaryItem::drawThumbnail(QPainter *painter)
{
//    updateBoundingRect();
    updateDrawPosition();
    painter->drawPixmap(drawCenter, *(m_pixmap.get()));
}


void GallaryItem::updateDrawPosition()
{
    QPoint topleft;
    QSize pixmapSize;

    pixmapSize = m_pixmap.get()->size();

//    topleft.setX((m_boundingRect.width() - pixmapSize.width()) / 2.0);
//    topleft.setY((m_boundingRect.height() - pixmapSize.height()) / 2.0);

    topleft.setX(0);
    topleft.setY(0);

    drawCenter = QRect(topleft, pixmapSize);
}

//void GallaryItem::showEvent(QShowEvent *event)
//{

//    HashKey key = g_directoryManager->getHashKey(m_entryStr);
//    m_pixmap = (*g_imageManager)[key]->getPixmap();

//    m_pixmapItem.setPixmap(*m_pixmap);
//    m_pixmapItem.show();
//}
