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

    // initialize private member
    // shared pointer methods?


    // MainWindow only controls Central Widget
    centralWidget.reset(new CentralWidget(this));
    setCentralWidget(centralWidget.get());

    QMenu* menu = new QMenu(this);
    menu->show();

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

//MainWindow

//
// Provide Connection with all other managers (ActionManager, DirectoryManager)
// View - Model Connection
//

void MainWindow::initConnect()
{
    qDebug() << "[Debug] MainWindow.cpp - Initial Connection";
    //ActionManager -> MainWindow (Received Action)
    connect(g_actionManager, &ActionManager::openActionPublished, g_mainWindow, &MainWindow::showOpenDialog);

    // private widget members connections

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



// Protected Events

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::RightButton)  {
        if(!contextMenu) {
             contextMenu.reset(new ContextMenu(this));
        }

        if(!contextMenu->isVisible()){
            QPoint pos = cursor().pos();
            contextMenu->showAt(pos);
        }
        event->accept();
//        emit onOpenAction("open");
    }
}


