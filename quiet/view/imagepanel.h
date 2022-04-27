#ifndef IMAGEPANEL_H
#define IMAGEPANEL_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <memory>
#include <QDebug>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QScrollBar>
#include <QList>

#include "model/actionmanager.h"
#include "model/directorymanager.h"
#include "model/imagemanager.h"
#include "object/image.h"
#include "settings.h"


class ImagePanel : public QGraphicsView
{
    Q_OBJECT
public:
    // initialization
    explicit ImagePanel(QWidget *parent = 0);
    ~ImagePanel();

private:
    QGraphicsScene* m_scene;
    QGraphicsPixmapItem m_pixmapItem;
    std::unique_ptr<QPixmap> m_pixmap;

    // reset before any display method
    void reset();
    void showImage(HashKey key);


    /////////

    // Initial Setup
    void initAttributes();
    void initConnect();
    void initLayout();

    // zoom Event
    qreal m_scale;
    QPointF m_currViewportCenter; // To keep track of zoom anchor
    QPoint m_mouseMoveStartPos; // To keep track of mouse dragging pos

    void zoomIn(const QPointF &pos);
    void zoomOut(const QPointF &pos);

protected:
    // Wheel Events
    void wheelEvent(QWheelEvent* event) override;
  
    // Mouse Events
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override; 

    // Enter Events (when mouse moves in (hover on) the widget or something enters)
    void enterEvent(QEvent* event) override;

    // Resize Window Event
    void resizeEvent(QResizeEvent* event) override;

signals:
 

public slots:
    void loadImage(const QString&);

    void zoomInReceiver();
    void zoomOutReceiver();
};

#endif // IMAGEPANEL_H
