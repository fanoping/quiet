#ifndef IMAGEPANEL_H
#define IMAGEPANEL_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <memory>
#include <QDebug>

#include "model/imagemanager.h"
#include "object/image.h"

class ImagePanel : public QWidget
{
    Q_OBJECT
public:
    explicit ImagePanel(QWidget *parent = 0);

    void initConnect();

private:
    std::shared_ptr<QPixmap> m_pixmap;

    QGraphicsPixmapItem m_pixmapItem;

signals:

public slots:
    bool showImage(std::shared_ptr<QPixmap> pixmap);

};

#endif // IMAGEPANEL_H
