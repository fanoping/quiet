#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <memory>

#include "view/imagepanel.h"
#include "view/gallarypanel.h"

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    // initialization
    explicit ImageWidget(QWidget *parent = 0);
    ~ImageWidget();

    // initialize connection
    void initConnect();


signals:

public slots:

private:
    QHBoxLayout m_layout;
    std::unique_ptr<ImagePanel> m_imagePanel;
    std::unique_ptr<GallaryPanel> m_gallaryPanel;

};

#endif // IMAGEWIDGET_H
