#include "gallaryitem.h"

GallaryItem::GallaryItem(QGraphicsItem *parent):
    QGraphicsWidget(parent),
    m_entryStr(""),
    m_size(128),
    m_paddingSize(0),
    m_hovered(false)
{
    initAttributes();
}

GallaryItem::GallaryItem(const QString& entryStr, QGraphicsItem *parent):
    QGraphicsWidget(parent),
    m_entryStr(entryStr),
    m_size(128),
    m_paddingSize(0),
    m_hovered(false)
{
     initAttributes();
}

GallaryItem::~GallaryItem()
{

}

void GallaryItem::initAttributes()
{
    this->setAttribute(Qt::WA_OpaquePaintEvent, true);
    this->setAcceptHoverEvents(true);
}


/*
 * Public
 */


void GallaryItem::setSize(int size)
{
    if(m_size == size || size <= 0) return;
    m_size = size;

    updateBoundingRect();
    updateGeometry();
    updateDrawPosition();
    update();
}

void GallaryItem::setPaddingSize(int paddingSize)
{
    if(m_paddingSize == paddingSize || paddingSize <= 0) return;
    m_paddingSize = paddingSize;

    updateBoundingRect();
    updateGeometry();
    updateDrawPosition();
    update();
}

void GallaryItem::updateBoundingRect()
{
    m_boundingRect = QRectF(0, 0, m_size + 2 * m_paddingSize, m_size + 2 * m_paddingSize);
}

void GallaryItem::updateGeometry()
{
    QGraphicsWidget::updateGeometry();
    // maybe need something else
}

void GallaryItem::updateDrawPosition()
{

    HashKey key = g_directoryManager->getHashKey(m_entryStr);
    m_pixmap = (*g_imageManager)[key]->getPixmap();

    qDebug() << m_pixmap->size();

    QSize pixmapSize = m_pixmap->size().scaled(m_size, m_size, Qt::KeepAspectRatio);
    QPoint topLeft;
    qDebug() << pixmapSize;
    topLeft.setX((m_boundingRect.width() - pixmapSize.width()) / 2.0 - m_paddingSize);
    topLeft.setY((m_boundingRect.height() - pixmapSize.height()) / 2.0 - m_paddingSize);

    m_contentRect = QRect(topLeft, pixmapSize);
}

void GallaryItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    HashKey key = g_directoryManager->getHashKey(m_entryStr);
    m_pixmap = (*g_imageManager)[key]->getPixmap();

    if(m_hovered) {
        drawHoverBackground(painter);
    }

    drawContent(painter);
}

void GallaryItem::drawContent(QPainter* painter)
{
    painter->drawPixmap(m_contentRect, *m_pixmap);
}

void GallaryItem::drawHoverBackground(QPainter* painter)
{
    painter->fillRect(m_boundingRect, QColor(70, 70, 70));
}


QSizeF GallaryItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which);
    Q_UNUSED(constraint);

    return m_boundingRect.size();
}

void GallaryItem::hoverEnterEvent(QGraphicsSceneHoverEvent*event)
{
    event->ignore();
    if(!m_hovered) {
        m_hovered = true;
        update();
    }
}

void GallaryItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*event)
{
    event->ignore();
    if(m_hovered) {
        m_hovered = false;
        update();
    }
}
