#ifndef GALLARYPANEL_H
#define GALLARYPANEL_H

#include <QWidget>
#include <QGraphicsView>

#include "view/gallaryitem.h"
#include "util/constants.h"

class GallaryPanel : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GallaryPanel(QWidget *parent = 0);
    ~GallaryPanel();

    void initConnect();

    // TODO: GallaryItem positioning

    void loadVisibleThumbnails();

private:
    QGraphicsScene* m_scene;
    QList<GallaryItem*> m_gallaryItems;


//    // Temporary Data for development
//    QList<QGraphicsPixmapItem*> tmpData;

    // Scrolling Preload
    int offsetPreloadRange = 1024;
    ScrollDirection previousScollDirection = SCROLL_INWARDS;

signals:

public slots:



};

#endif // GALLARYPANEL_H
