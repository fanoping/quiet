#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <memory>

#include "view/imagepanel.h"

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);

    void showImage(std::shared_ptr<QPixmap> image);

signals:

public slots:

private:
    QVBoxLayout m_layout;
    std::shared_ptr<ImagePanel> m_imagePanel;


};

#endif // IMAGEWIDGET_H
