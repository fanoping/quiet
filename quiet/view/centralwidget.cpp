#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent) : QStackedWidget(parent)
{
    imageWidget.reset(new ImageWidget(this));
}

