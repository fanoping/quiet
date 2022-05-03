#include "appearancetab.h"

AppearanceTab::AppearanceTab(QWidget *parent) : QWidget(parent)
{
    initAttributes();
    initLayout();
    initConnect();
}

AppearanceTab::~AppearanceTab()
{
    if(m_appearanceSelection) {
        delete m_appearanceSelection;
    }
}

void AppearanceTab::initAttributes()
{

}

void AppearanceTab::initLayout()
{
    // Form layout alignment
    m_layout.setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);

    // Appearance Selection
    m_appearanceSelection = new QComboBox(this);

    QStringList appearanceOptions;
    appearanceOptions << "Light" << "Dark";
    m_appearanceSelection->addItems(appearanceOptions);

    // Final add up
    m_layout.addRow(tr("Appearance:"), m_appearanceSelection);
    this->setLayout(&m_layout);
}

void AppearanceTab::initConnect()
{
    // Connect with the settingsManager
    connect(m_appearanceSelection ,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), g_settingsManager, &Settings::setThemePalette);

}
