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

#include "model/imagemanager.h"
#include "object/image.h"

class ImagePanel : public QGraphicsView
{
    Q_OBJECT
public:
    // initialization
    explicit ImagePanel(QWidget *parent = 0);
    ~ImagePanel();

    // initialize connection
    void initConnect();

private:
    QGraphicsScene* m_scene;
    QGraphicsPixmapItem m_pixmapItem;
    std::unique_ptr<QPixmap> m_pixmap;

    // reset before any display method
    void reset();

    // zoom Event
    qreal m_scale;
    void zoom(qreal scaler, const QPoint &pos);




protected:
  void wheelEvent(QWheelEvent* event) override;



signals:


public slots:
    void showImage(std::shared_ptr<Image> image);

};

#endif // IMAGEPANEL_H
