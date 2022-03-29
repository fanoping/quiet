#include "contextmenu.h"
#include "ui_contextmenu.h"

ContextMenu::ContextMenu(QWidget *parent) :
    QMenu(parent),
    ui(new Ui::ContextMenu)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Popup);
//    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_NoMousePropagation, false);
    this->hide();

    // UI settup
    ui->open->setAction("open");
    ui->open->setText(tr("Open"));

    ui->open->setEnabled(false);

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

void ContextMenu::paintEvent(QPaintEvent *event)
{
    QStyleOption option;
    option.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &p, this);
}
