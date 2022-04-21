#ifndef GALLARYPANEL_H
#define GALLARYPANEL_H

#include <QWidget>
#include <QGraphicsView>
#include <QScrollBar>
#include <QVBoxLayout>

#include "model/directorymanager.h"
#include "view/gallaryitem.h"
#include "util/constants.h"
#include "util/settings.h"

class GallaryPanel : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GallaryPanel(QWidget *parent = 0);
    ~GallaryPanel();

private:
    QVBoxLayout m_layout;
    QGraphicsScene* m_scene;
    QList<GallaryItem*> m_gallaryItems;
    QScrollBar* m_scrollBar;

    void loadVisibleThumbnails();

    // Scrolling Preload
    int offsetPreloadRange = 128;
    ScrollDirection previousScollDirection = SCROLL_INWARDS;

///////////

    // Initial Setup
    void initAttributes();
    void initConnect();
    void initLayout();
    void initSettings();

    // Initial Creation and Reset
   GallaryItem* createGallaryItem(const QString& entryStr);
   void resetGallaryItems();

   // GallaryItem Attributes
   int m_gallaryItemSize;    // Base square size of GallaryItem
   int m_gallaryItemPaddingSize;

   // Collection of Status
   // Selection
   QList<int> m_selectedPos;

   // Update methods when initial creation or recreation occurs
   // - file insertion or removed
   // - resize event (window size)
   // - padding size changes

   // GallaryItem position update (default 0 to count - 1)
   void updateGallaryItemPositions();

   // GallaryItem position update
   void updateGallaryItemPositions(int start, int end);

   // Scene Size update (in order to match up with its content)
   void updateSceneSize();

   // GallaryItem selection update
   void updateGallaryItemSelection(const QList<int>& selection);

   // Utility functions
   // Check valid pos is inrange
   bool validPosition(int pos);

   // Ensure visible with respect to pos
   void ensureItemVisible(int pos);


protected:
   // Mouse Events
   void mousePressEvent(QMouseEvent* event) override;

   // Window Resize
   void resizeEvent(QResizeEvent* event) override;


signals:
   void onSelectedItems(const QString&);


public slots:
    void showEvent(QShowEvent *event) override;
    void loadGallaryItems(const QString&, const QList<QString>&);

};

#endif // GALLARYPANEL_H
