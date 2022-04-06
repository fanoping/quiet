#ifndef IMAGEPANEL_H
#define IMAGEPANEL_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <memory>
#include <QDebug>
#include <QGraphicsView>

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
    std::unique_ptr<QPixmap> m_pixmap;


    QGraphicsScene* m_scene;

    QGraphicsPixmapItem m_pixmapItem;

signals:

public slots:
    void showImage(std::shared_ptr<Image> image);

};

#endif // IMAGEPANEL_H
