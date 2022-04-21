#include "imagewidget.h"
#include <QtWidgets>
#include <QScrollArea>

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
     // init
    m_imagePanel.reset(new ImagePanel(this));
    m_gallaryPanel.reset(new GallaryPanel(this));

    m_layout.setContentsMargins(0, 0, 0, 0);
    m_layout.setSpacing(0);

    m_layout.addWidget(m_imagePanel.get());
    m_layout.addWidget(m_gallaryPanel.get());

    m_imagePanel->show();
    m_gallaryPanel->show();

    setLayout(&m_layout);
}

ImageWidget::~ImageWidget()
{

}

void ImageWidget::initConnect()
{
    // Private widgets connections
    connect(m_gallaryPanel.get(), &GallaryPanel::onSelectedItems, m_imagePanel.get(), &ImagePanel::loadImage);
}

