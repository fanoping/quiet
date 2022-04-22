#include "mainwindow.h"

//                                                                      - [ImageWidget]
//                                                                    |
// [MainWindow] - [CentralWidget] -
//                                                                    |
//                                                                      -


MainWindow* g_mainWindow = nullptr;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initAttibutes();
    initLayout();
}

MainWindow::~MainWindow()
{

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
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    // Receives mouse move events even if no buttons are pressed.
    this->setMouseTracking(true);

    // Keyboard Focis (default disable)
    this->setFocusPolicy(Qt::NoFocus);

    // Set minimum window size (Minimum size after resizing)
    this->setMinimumSize(480, 360);
}

void MainWindow::initLayout()
{
    // MenuBar Settings
    file = this->menuBar()->addMenu("File");
    file->addAction("Open");
    connect(file, &QMenu::triggered, g_actionManager, &ActionManager::actionReceiver);

    contextMenu = file;

    // Layout Settings
    // MainWindow only controls Central Widget
    centralWidget.reset(new CentralWidget(this));
    this->setCentralWidget(centralWidget.get());

}


//MainWindow

//
// Provide Connection with all other managers (ActionManager, DirectoryManager)
// View - Model Connection
//

void MainWindow::initConnect()
{
    qDebug() << "[Debug] MainWindow.cpp - Initial Connection";
    //ActionManager -> MainWindow (Received Action)
    connect(g_actionManager, &ActionManager::open, g_mainWindow, &MainWindow::showOpenDialog);

}



// private slots

//
// Open File Dialog Window
//

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


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMainWindow::contextMenuEvent(event);
    contextMenu->popup(event->globalPos());
}


