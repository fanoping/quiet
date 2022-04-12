#ifndef GALLARYPANEL_H
#define GALLARYPANEL_H

#include <QWidget>
#include <QGraphicsView>


class GallaryPanel : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GallaryPanel(QWidget *parent = 0);
    ~GallaryPanel();

    void initConnect();

private:
    QGraphicsScene* m_scene;


signals:

public slots:
};

#endif // GALLARYPANEL_H
