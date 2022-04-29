#include "appearancetab.h"

AppearanceTab::AppearanceTab(QWidget *parent) : QWidget(parent)
{
    initAttributes();
    initLayout();
}

AppearanceTab::~AppearanceTab()
{

}

void AppearanceTab::initAttributes()
{

}

void AppearanceTab::initLayout()
{

    m_layout.setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lineEdit = new QLineEdit();
    lineEdit2 = new QLineEdit();

    QLabel l("App");
    l.setAlignment(Qt::AlignRight);
    m_layout.addRow(&l);
    m_layout.addRow(tr("App123414124124"), lineEdit2);

    this->setLayout(&m_layout);

}
