#ifndef GALLARYPANEL_H
#define GALLARYPANEL_H

#include <QWidget>
#include <QGraphicsView>
#include <QScrollBar>

#include "model/directorymanager.h"
#include "view/gallaryitem.h"
#include "util/constants.h"

class GallaryPanel : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GallaryPanel(QWidget *parent = 0);
    ~GallaryPanel();



    // TODO: GallaryItem positioning


//     void initConnet();


private:
    QGraphicsScene* m_scene;
    QList<GallaryItem*> m_gallaryItems;
    QScrollBar* m_scrollBar;

    void loadVisibleThumbnails();

    // Scrolling Preload
    int offsetPreloadRange = 1024;
    ScrollDirection previousScollDirection = SCROLL_INWARDS;

///////////


    // Initial Setup
    void initAttributes();
    void initConnect();
    void initLayout();
    void initSettings();

    // Initial Creation
   GallaryItem* createGallaryItem(const QString& entryStr);

   // GallaryItem Attributes
   int m_gallaryItemSize;    // Base square size of GallaryItem
   int m_gallaryItemPaddingSize;

   // Update methods when initial creation or recreation occurs
   // - file insertion or removed
   // - resize event (window size)
   // - padding size changes

   // GallaryItem position update
   void updateGallaryItemPositions();
   void updateGallaryItemPositions(int start, int end);

   // Scene Size update (in order to match up with its content)
   void updateSceneSize();

   // Utility functions
   bool validPosition(int pos);
   void ensureItemVisible(int pos);



signals:

public slots:
    void showEvent(QShowEvent *event) override;
    void loadThumbnails(const QString&, const QList<QString>&);

};

#endif // GALLARYPANEL_H
