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
    // Window Title
    // Hide question mark of the window title (it shows ? in default)
    this->setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint | Qt::CustomizeWindowHint));
    this->setWindowTitle("Settings");

    this->setMinimumSize(435, 482);
}

void SettingsDialog::initLayout()
{
    m_tabbar.reset(new QTabWidget(this));

    m_apperanceTab.reset(new AppearanceTab(this));
    m_tabbar.get()->addTab(m_apperanceTab.get(), "Appearance");


    m_layout.addWidget(m_tabbar.get());
    this->setLayout(&m_layout);
}

int SettingsDialog::exec()
{
    return QDialog::exec();
}
