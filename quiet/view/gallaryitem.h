#ifndef GALLARYITEM_H
#define GALLARYITEM_H

#include <QGraphicsWidget>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <memory>

#include "model/directorymanager.h"
#include "model/imagemanager.h"
#include "object/image.h"
#include "util/constants.h"
#include "util/utils.h"


/*
 *  TODO:
 * - update Geometry
 * - selection method with painting changes
 */


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

    void loaded();
    void unload();

    ///////////

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setSize(int size);
    void setPaddingSize(int paddingSize);


private:

    void initAttributes();

    QString m_entryStr;



   std::unique_ptr<QPixmap> m_pixmap;

   /////////////////////////////////////////

protected:
   QRectF m_boundingRect;
   QRect m_contentRect;

   // Attributes
   int m_size;
   int m_paddingSize;

   // Status bool
   bool m_hovered;

    // Update methods when initial creation or recreation occurs
   // - file insertion or removed
   // - resize event (window size)
   // - padding size / item size changes

   // Update Item Bounds
   void updateBoundingRect();

   // Notifies the layout system that this widget has changed (TODO)
   void updateGeometry() override;

   // Update Drawing Position
   void updateDrawPosition();

   // Drawing function - induced by paint function
   void drawContent(QPainter* painter);
   void drawHoverBackground(QPainter* painter);

   // Size hint: to make parent class access to its size attribute by using itemsboundingRect
   QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;

   // Hover Events
   void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
   void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;



signals:

public slots:

};

#endif // GALLARYITEM_H
