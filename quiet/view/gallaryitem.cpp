#include "gallaryitem.h"

// GallaryItem::GallaryItem(QGraphicsItem *parent):
//     QGraphicsWidget(parent),
//     m_entryStr(""),
//     m_size(128),
//     m_paddingSize(0),
//     m_hovered(false),
//     m_selected(false)
// {
//     initAttributes();
// }

GallaryItem::GallaryItem(const QString& entryStr, QGraphicsItem *parent):
    QGraphicsWidget(parent),
    m_entryStr(entryStr),
    m_size(128),
    m_paddingSize(0),
    m_hovered(false),
    m_selected(false)
{
     initAttributes();
}

GallaryItem::~GallaryItem()
{

}

void GallaryItem::initAttributes()
{
    // Indicates that the widget will paint over its entire area with opaque colors.
    this->setAttribute(Qt::WA_OpaquePaintEvent, true);

    // Accept Mouse Event
    this->setAcceptHoverEvents(true);

    // font attributes
    font.setBold(false);
    m_textHeight = QFontMetrics(font).height();
}


void GallaryItem::setSize(int size)
{
    if(m_size == size || size <= 0) return;
    m_size = size;

    updateGeometry();
}

void GallaryItem::setPaddingSize(int paddingSize)
{
    if(m_paddingSize == paddingSize || paddingSize <= 0) return;
    m_paddingSize = paddingSize;

    updateGeometry();
}

int GallaryItem::getSize()
{
    return m_size;
}

int GallaryItem::getPaddingSize()
{
    return m_paddingSize;
}

QRectF GallaryItem::boundingRect() const
{
    return m_boundingRect;
}


void GallaryItem::setSelected(bool select)
{
    m_selected = select;
    update();
}

void GallaryItem::updateBoundingRect()
{
    m_boundingRect = QRectF(0, 0, m_size + 6 * m_paddingSize, m_size + m_textHeight + 8 * m_paddingSize);

}

void GallaryItem::updateGeometry()
{
    updateBoundingRect();
    updateDrawPosition();
    updateFilenamePosition();
    QGraphicsWidget::updateGeometry();
    update();
}

void GallaryItem::updateDrawPosition()
{
    // should be moved out
    if(!m_pixmap) {
        HashKey key = g_directoryManager->getHashKey(m_entryStr);
        m_pixmap = (*g_imageManager)[key]->getPixmap();
    }
    QSize pixmapSize = m_pixmap->size().scaled(m_size, m_size, Qt::KeepAspectRatio);
    QPoint topLeft;

    topLeft.setX((m_boundingRect.width() - pixmapSize.width()) / 2.0);
    topLeft.setY((m_boundingRect.height() - m_textHeight - pixmapSize.height()) / 2.0 - m_paddingSize);

    m_contentRect = QRect(topLeft, pixmapSize);
}

void GallaryItem::updateFilenamePosition()
{
    // m_filenameRect = QRect(m_paddingSize, m_size + 3 * m_paddingSize, m_size, m_textHeight);
    m_filenameRect = QRect(3 * m_paddingSize, m_size + 5 * m_paddingSize, m_size, m_textHeight);
}

void GallaryItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    
    if(!m_pixmap) {
        HashKey key = g_directoryManager->getHashKey(m_entryStr);
        m_pixmap = (*g_imageManager)[key]->getPixmap();
    }
    if(m_selected) {
        drawSelectBackground(painter);
    } else {
        if(m_hovered) {
            drawHoverBackground(painter);
        }
    }
    drawContent(painter);
    drawFilename(painter);
}

void GallaryItem::drawContent(QPainter* painter)
{
    painter->fillRect(m_contentRect.adjusted(2, 2, 2, 2), g_settingsManager->themePalette().shadowColor);
    painter->drawPixmap(m_contentRect, *m_pixmap);
}

void GallaryItem::drawHoverBackground(QPainter* painter)
{
    painter->fillRect(m_boundingRect.adjusted(m_paddingSize, m_paddingSize, -m_paddingSize, -m_paddingSize), g_settingsManager->themePalette().tertiaryBackground);
}

void GallaryItem::drawSelectBackground(QPainter *painter)
{
    painter->setOpacity(0.2);
    painter->fillRect(m_boundingRect.adjusted(m_paddingSize, m_paddingSize, -m_paddingSize, -m_paddingSize), g_settingsManager->themePalette().themeColor);

    qreal penWidth = 0.5;
    QPen pen(g_settingsManager->themePalette().themeColor, penWidth);
    painter->setOpacity(0.3);
    painter->setPen(pen);
    painter->drawRect(m_boundingRect.adjusted(m_paddingSize + penWidth, m_paddingSize + penWidth, -m_paddingSize + penWidth, -m_paddingSize + penWidth));

    painter->setOpacity(1.0);
}

void GallaryItem::drawFilename(QPainter *painter)
{
   QFileInfo fileInfo = g_directoryManager->getFileInfo(m_entryStr);
   painter->setFont(font);
   painter->setPen(g_settingsManager->themePalette().primaryLabel);
   painter->drawText(m_filenameRect, Qt::TextSingleLine | Qt::AlignVCenter | Qt::AlignHCenter ,fileInfo.fileName());
}

QSizeF GallaryItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which);
    Q_UNUSED(constraint);

    return m_boundingRect.size();
}

void GallaryItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    event->ignore();
    if(!m_hovered) {
        m_hovered = true;
        update();
    }
}

void GallaryItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    event->ignore();
    if(m_hovered) {
        m_hovered = false;
        update();
    }
}
