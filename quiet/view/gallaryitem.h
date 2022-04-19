#ifndef GALLARYITEM_H
#define GALLARYITEM_H

#include <QGraphicsWidget>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <memory>

#include "model/directorymanager.h"
#include "model/imagemanager.h"
#include "object/image.h"
#include "util/constants.h"
#include "util/utils.h"


class GallaryItem : public QGraphicsWidget
{
    Q_OBJECT
public:

    /*
     *
     * TODO:
     * Reimplement methods:
     * - Protected: https://doc.qt.io/qt-5/qgraphicswidget.html#reimplemented-protected-functions
     * - Public: https://doc.qt.io/qt-5/qgraphicswidget.html#reimplemented-public-functions
     *
     */

    explicit GallaryItem(QGraphicsItem *parent = 0);
    explicit GallaryItem(const QString& entryStr="", QGraphicsItem *parent = 0);
    ~GallaryItem();

    // Public Geometry Settings/Modifier
    void size(qreal x, qreal y); // or resize

    void loaded();
    void unload();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    QRectF m_boundingRect;
    qreal m_sizeX,  m_sizeY;

    qreal m_paddingTop, m_paddingBottom, m_paddingLeading, m_paddingTrailing;   // Top, bottom, Leading, Trailing

    QString m_entryStr;

    // status
    bool m_bHovered, m_bSelected;

    // geometry modifier
    void updateBoundingRect();

    void drawThumbnail(QPainter* painter);

    void updateDrawPosition();

   std::unique_ptr<QPixmap> m_pixmap;
   QGraphicsPixmapItem m_pixmapItem;

   QRect drawCenter;



signals:

public slots:
};

#endif // GALLARYITEM_H
