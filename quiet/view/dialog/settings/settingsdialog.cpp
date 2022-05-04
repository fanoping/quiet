#include "settingsdialog.h"


SettingsDialog::SettingsDialog(QWidget *parent):
    QDialog(parent)
{
    initAttributes();
    initLayout();
    initConnect();
}

SettingsDialog::~SettingsDialog()
{
    if(m_buttonOK) delete m_buttonOK;
    if(m_buttonApply) delete m_buttonApply;
    if(m_buttonCancel) delete m_buttonCancel;
}

void SettingsDialog::initAttributes()
{
    // Window Title
    // Hide question mark of the window title (it shows ? in default)
    this->setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint | Qt::CustomizeWindowHint));

    // Window Geometry
    this->setWindowTitle("Settings");
    this->setMinimumSize(435, 482);
}

void SettingsDialog::initLayout()
{
    // Option Layout
    m_tabbar.reset(new QTabWidget(this));

    m_apperanceTab.reset(new AppearanceTab(this));
    m_tabbar.get()->addTab(m_apperanceTab.get(), "Appearance");

    // Button Layout
    m_buttonOK = new QPushButton("OK");
    m_buttonApply = new QPushButton("Apply");
    m_buttonCancel = new QPushButton("Cancel");
    m_buttonOK->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_buttonApply->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_buttonCancel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    m_buttonOK->setFocus(Qt::ActiveWindowFocusReason);

    m_buttonLayout.addStretch();
    m_buttonLayout.addWidget(m_buttonOK);
    m_buttonLayout.addWidget(m_buttonApply);
    m_buttonLayout.addWidget(m_buttonCancel);

    // Put it together
    m_layout.addWidget(m_tabbar.get());
    m_layout.addLayout(&m_buttonLayout);
    this->setLayout(&m_layout);
}

void SettingsDialog::initConnect()
{
    // For Button Reactions Connection
    connect(m_buttonCancel, &QPushButton::clicked, this, &SettingsDialog::close);
}

int SettingsDialog::exec()
{
    return QDialog::exec();
}

void SettingsDialog::closeEvent(QCloseEvent* event)
{
    event->accept();
    emit settingsDialogClosed();
}
