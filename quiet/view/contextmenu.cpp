#include "contextmenu.h"
#include "ui_contextmenu.h"

ContextMenu::ContextMenu(QWidget *parent) :
    QMenu(parent),
    ui(new Ui::ContextMenu)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Popup);
    this->hide();

    // UI settup
    ui->open->setAction("openAction");
    ui->open->setText(tr("Open"));

//    QAction* newAction = new QAction(this);
//    newAction->setText(tr("Open"));
//    this->addAction(newAction);
}

ContextMenu::~ContextMenu()
{
    delete ui;
}



void ContextMenu::showAt(QPoint pos)
{
    QRect geo = geometry();
    geo.moveTopLeft(pos);
    setGeometry(geo);
    this->show();
}

void ContextMenu::setGeometry(QRect geo)
{
    QWidget::setGeometry(geo);
}


void ContextMenu::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    this->hide();
}
