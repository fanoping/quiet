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

signals:

public slots:

private:
    QVBoxLayout layout;
    std::shared_ptr<ImagePanel>  imagePanel;


};

#endif // IMAGEWIDGET_H
