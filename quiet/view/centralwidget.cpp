#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent) : QStackedWidget(parent)
{
    m_imageWidget.reset(new ImageWidget(this));

    this->addWidget(m_imageWidget.get());

    // initial view in image panel
    toggleWidget(VIEW_IMAGE);

    initConnect();
}

CentralWidget::~CentralWidget()
{
    if(m_imageWidget){
        m_imageWidget.reset();
    }
}

void CentralWidget::initConnect()
{
    // init connection

    // private members connection
    m_imageWidget.get()->initConnect();
}





/*

  Public Slots

*/

void CentralWidget::toggleWidget(ViewLayer viewIndex)
{
    if (viewIndex == m_viewIndex) return;
    setCurrentIndex(viewIndex);
    widget(viewIndex)->show();
    widget(viewIndex)->setFocus();
}
