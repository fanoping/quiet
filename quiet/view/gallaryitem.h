#ifndef GALLARYITEM_H
#define GALLARYITEM_H

#include <QGraphicsWidget>
#include <QGraphicsItem>
#include <QRectF>

#include "object/image.h"
#include "util/constants.h"


class GallaryItem : public QGraphicsWidget
{
    Q_OBJECT
public:

    /*
     *
     * TODO:
     * Reimplement methods:
     * - Protected:　https://doc.qt.io/qt-5/qgraphicswidget.html#reimplemented-protected-functions
     * - Public: https://doc.qt.io/qt-5/qgraphicswidget.html#reimplemented-public-functions
     *
     */

    explicit GallaryItem(QGraphicsItem *parent = 0);
    ~GallaryItem();

    // Public Geometry Settings/Modifier
    void padding(qreal length, Edges edges=ALL);   // or setContentsMargins
    void size(qreal x, qreal y); // or resize


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    QRectF m_boundingRect;
    qreal m_sizeX,  m_sizeY;

    qreal m_paddingTop, m_paddingBottom, m_paddingLeading, m_paddingTrailing;   // Top, bottom, Leading, Trailing

    // status
    bool m_bHovered, m_bSelected;

    // geometry modifier
    void updateBoundingRect();

    // content
    std::unique_ptr<Image> m_image;

signals:

public slots:
};

#endif // GALLARYITEM_H
