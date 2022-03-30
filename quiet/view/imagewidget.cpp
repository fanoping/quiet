#include "imagewidget.h"
#include <QtWidgets>
#include <QScrollArea>

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
     // init
    m_imagePanel.reset(new ImagePanel(this));
    m_imagePanel.get()->initConnect();

    m_layout.setContentsMargins(0, 0, 0, 0);
    m_layout.setSpacing(0);


    m_layout.addWidget(m_imagePanel.get());
    m_imagePanel.get()->show();

    setLayout(&m_layout);
}

void ImageWidget::showImage(std::shared_ptr<QPixmap> image)
{
   qDebug()<<"centrala";
    m_imagePanel->showImage(std::move(image));
}
