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
    // initialization
    explicit ImageWidget(QWidget *parent = 0);
    ~ImageWidget();

    // initialize connection
    void initConnect();


signals:

public slots:

private:
    QVBoxLayout m_layout;
    std::unique_ptr<ImagePanel> m_imagePanel;


};

#endif // IMAGEWIDGET_H
