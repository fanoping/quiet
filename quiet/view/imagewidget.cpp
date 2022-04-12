#include "imagewidget.h"
#include <QtWidgets>
#include <QScrollArea>

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
     // init
    m_imagePanel.reset(new ImagePanel(this));
    m_imagePanel->initConnect();

    m_layout.setContentsMargins(0, 0, 0, 0);
    m_layout.setSpacing(0);

    m_layout.addWidget(m_imagePanel.get());
    m_imagePanel->show();

    setLayout(&m_layout);
}

ImageWidget::~ImageWidget()
{

}

void ImageWidget::initConnect()
{
    // private widgets initialization
    m_imagePanel.get()->initConnect();
}

