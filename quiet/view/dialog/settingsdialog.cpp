#include "settingsdialog.h"


SettingsDialog::SettingsDialog(QWidget *parent):
    QDialog(parent)
{
    initAttributes();
    initLayout();
}

SettingsDialog::~SettingsDialog()
{
    
}


void SettingsDialog::initAttributes()
{

}

void SettingsDialog::initLayout()
{

}

int SettingsDialog::exec()
{
    return QDialog::exec();
}
