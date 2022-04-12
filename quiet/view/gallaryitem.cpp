#include "gallaryitem.h"

GallaryItem::GallaryItem(QGraphicsItem *parent):
    QGraphicsWidget(parent),
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

void GallaryItem::padding(qreal length, Edges edges)
{
    if(length <= 0 ) return;

    switch (edges) {
    case ALL:
        m_paddingTop = length;
        m_paddingBottom = length;
        m_paddingLeading = length;
        m_paddingTrailing = length;
    case TOP:
        m_paddingTop = length;
    case BOTTOM:
        m_paddingBottom = length;
    case LEADING:
        m_paddingLeading = length;
    case TRAILING:
        m_paddingTrailing = length;
    case HORIZONTAL:
        m_paddingLeading = length;
        m_paddingTrailing = length;
    case VERTICAL:
        m_paddingTop = length;
        m_paddingBottom = length;
    default:  // Same as Edges.ALL
        m_paddingTop = length;
        m_paddingBottom = length;
        m_paddingLeading = length;
        m_paddingTrailing = length;
    }

    updateBoundingRect();
}


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


    // Selected, Hovered Background Painter


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
