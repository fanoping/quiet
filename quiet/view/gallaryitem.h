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
#include "settings.h"


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

    // explicit GallaryItem(QGraphicsItem *parent = 0);
    explicit GallaryItem(const QString& entryStr="", QGraphicsItem *parent = 0);
    ~GallaryItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Geometry Settings
    void setSize(int size);
    void setPaddingSize(int paddingSize);

    int getSize();
    int getPaddingSize();

    // Selection Settings
    void setSelected(bool select);



    QString getStr() { return m_entryStr; }
private:
    // Initial Setup
    void initAttributes();

    QString m_entryStr;
   std::unique_ptr<QPixmap> m_pixmap;

   /////////////////////////////////////////

   // Containers which diaplay info
   QRectF m_boundingRect;
   QRect m_contentRect;
   QRect m_filenameRect;

   // Attributes
   int m_size;
   int m_paddingSize;
   int m_textHeight;

   QFont font;

   // Collection of Status
   // Hover
   bool m_hovered;

   // Selection
   bool m_selected;

    // Update methods when initial creation or recreation occurs
   // - file insertion or removed
   // - resize event (window size)
   // - padding size / item size changes

   // Notifies the layout system that this widget has changed
   void updateGeometry() override;

   // Update Item Bounds
   void updateBoundingRect();

   // Update Drawing Position
   void updateDrawPosition();

   // Update Filename Position
   void updateFilenamePosition();

   // Drawing function - induced by paint function
   void drawContent(QPainter* painter);
   void drawHoverBackground(QPainter* painter);
   void drawSelectBackground(QPainter* painter);
   void drawFilename(QPainter* painter);

   // Size hint: to make parent class access to its size attribute by using itemsboundingRect
   QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;

   // Hover Events
   void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
   void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;



signals:

public slots:

};

#endif // GALLARYITEM_H
