#include "gallarypanel.h"

GallaryPanel::GallaryPanel(QWidget *parent) : QGraphicsView(parent)
{
    // Widget Settings
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


}

GallaryPanel::~GallaryPanel()
{

}


void GallaryPanel::initConnect()
{

}
