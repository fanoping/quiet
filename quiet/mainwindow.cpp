#include "mainwindow.h"

//                                                                      - [ImageWidget]
//                                                                    |
// [MainWindow] - [CentralWidget] -
//                                                                    |
//                                                                      -


//
// TODOs:
// - move ContextMent Event to child widgets
// 

MainWindow* g_mainWindow = nullptr;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initAttibutes();
    initLayout();
}

MainWindow::~MainWindow()
{
    foreach(Action* action, m_actionList) {
        delete action;
    }
}

MainWindow* MainWindow::getInstance()
{
    if(!g_mainWindow) {
        g_mainWindow = new MainWindow();
        initConnect();
    }
    return g_mainWindow;
}

void MainWindow::initAttibutes()
{
    // Receives mouse move events even if no buttons are pressed.
    this->setMouseTracking(true);

    // Keyboard Focis (default disable)
    this->setFocusPolicy(Qt::NoFocus);

    // Set minimum window size (Minimum size after resizing)
    this->setMinimumSize(800, 600);

    // Set Window Title
    this->setWindowTitle(QCoreApplication::applicationName() + " v" + QCoreApplication::applicationVersion());
}

void MainWindow::initLayout()
{
    // Menu Settings
    buildFileMenu();
    buildViewMenu();
    buildContextMenu();

    // MenuBar Settings
    buildMenuBar();

    // Layout Settings
    // MainWindow only controls Central Widget
    m_centralWidget.reset(new CentralWidget(this));
    this->setCentralWidget(m_centralWidget.get());

    // Dialog Setups
    m_settingsDialog.reset(new SettingsDialog(this));

}

void MainWindow::initConnect()
{
    qDebug() << "[Debug] MainWindow.cpp - Initial Connection Settings";

    //ActionManager -> MainWindow (Received Action)
    connect(g_actionManager, &ActionManager::open, g_mainWindow, &MainWindow::showOpenDialog, Qt::UniqueConnection);
    connect(g_actionManager, &ActionManager::settings, g_mainWindow, &MainWindow::showSettingsDialog, Qt::UniqueConnection);
}

void MainWindow::buildFileMenu()
{
    m_fileMenu.reset(new QMenu("File", this));
    Action* action;

    if(action = buildSingleAction("open")){
        m_fileMenu.get()->addAction(action);
    }

    m_fileMenu.get()->addSeparator();

    if(action = buildSingleAction("settings")){
        m_fileMenu.get()->addAction(action);
    }

    connect(m_fileMenu.get(), &QMenu::triggered, g_actionManager, &ActionManager::actionReceiver,  Qt::UniqueConnection);
}

void MainWindow::buildViewMenu()
{
    m_viewMenu.reset(new QMenu("View", this));
    Action* action;

    if(action = buildSingleAction("zoomIn")) {
        m_viewMenu.get()->addAction(action);
    }

    if(action = buildSingleAction("zoomOut")) {
        m_viewMenu.get()->addAction(action);
    }
    m_viewMenu.get()->addSeparator();

    connect(m_viewMenu.get(), &QMenu::triggered, g_actionManager, &ActionManager::actionReceiver,  Qt::UniqueConnection);
}

void MainWindow::buildContextMenu()
{
    m_contextMenu.reset(new QMenu(this));
    Action* action;
    

    if(action = buildSingleAction("open")) {
        m_contextMenu.get()->addAction(action);
    }
    
    // Menu
    QMenu* viewMenu = new QMenu("View", this);
    if(action = buildSingleAction("zoomIn")) {
        viewMenu->addAction(action);
    }

    if(action = buildSingleAction("zoomOut")) {
        viewMenu->addAction(action);
    }
    
    m_contextMenu.get()->addSeparator();
    m_contextMenu.get()->addMenu(viewMenu);
    
    connect(m_contextMenu.get(), &QMenu::triggered, g_actionManager, &ActionManager::actionReceiver,  Qt::UniqueConnection);
}

void MainWindow::buildMenuBar()
{
    if(!m_fileMenu.get()) return;

    QString style = "";
    style += "QMenuBar { background:" + g_settingsManager->themePalette().secondaryBackground.name(QColor::HexArgb) + "; }";
    // For Each Item
    style += "QMenuBar::item { background:" + g_settingsManager->themePalette().secondaryBackground.name(QColor::HexArgb) +"; }";
    style += "QMenuBar::item { color:" + g_settingsManager->themePalette().primaryLabel.name(QColor::HexArgb) +"; }";
    style += "QMenuBar::item:selected { background:" + g_settingsManager->themePalette().tertiaryBackground.name(QColor::HexArgb) +"; }";

    QColor pressedColor = g_settingsManager->themePalette().themeColor;
    pressedColor.setAlphaF(0.3);
    style += "QMenuBar::item:pressed { background:" + pressedColor.name(QColor::HexArgb) +"; }";

    this->menuBar()->setStyleSheet(style);

    this->menuBar()->addMenu(m_fileMenu.get());
    this->menuBar()->addMenu(m_viewMenu.get());
}

Action* MainWindow::buildSingleAction(const QString& actionName)
{
    ActionAttributes attributes;
    if(!g_actionManager->cloneAction(actionName, attributes)) return nullptr;
//    qDebug() << actionName;
    Action* action = new Action(actionName, attributes.text);
    action->setShortcut(attributes.shortcut);


    m_actionList.append(action);
    
    return action;
}


void MainWindow::showOpenDialog()
{
    qDebug() << "[Debug] MainWindow.cpp - Open dialog triggered";
    QFileDialog dialog(this);
    QStringList filters;
    filters.append(g_settingsManager->supportedFormatStr());
    filters.append("All Files (*)");
    dialog.setDirectory(g_directoryManager->getDirectory());
    dialog.setNameFilters(filters);
    dialog.setWindowTitle("Open File");
    dialog.setWindowModality(Qt::ApplicationModal);
    connect(&dialog, &QFileDialog::fileSelected, g_directoryManager, &DirectoryManager::dirReceived);
    dialog.exec();
}

void MainWindow::showSettingsDialog()
{
    m_settingsDialog.get()->exec();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    if(m_contextMenu) {
        QMainWindow::contextMenuEvent(event);
        m_contextMenu->popup(event->globalPos());
    } else {
        event->ignore();
    }
}


