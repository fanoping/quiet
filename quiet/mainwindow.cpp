#include "mainwindow.h"


MainWindow* g_mainWindow = nullptr;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // initialize private member
    // shared pointer methods?

    //                                                                      - [ImageWidget]
    //                                                                    |
    // [MainWindow] - [CentralWidget] -
    //                                                                    |
    //                                                                      -


    // MainWindow only controls Central Widget

    centralWidget.reset(new CentralWidget(this));

}

MainWindow::~MainWindow()
{


}

MainWindow* MainWindow::getInstance()
{
    if(!g_mainWindow) {
        g_mainWindow = new MainWindow();

    }
    return g_mainWindow;
}


//
// Provide Connection with all other managers (ActionManager, DirectoryManager)
// View - Model Connection
//

void MainWindow::initConnect()
{
    qDebug() << "[Debug] MainWindow.cpp - Initial Connection";

    //ActionManager -> MainWindow (Received Action)
    connect(g_actionManager, &ActionManager::openActionPublished, g_mainWindow, &MainWindow::showOpenDialog);

    connect(g_imageManager, &ImageManager::imageLoaded, g_mainWindow, &MainWindow::showImage);


}



// private slots

//
// Open File Dialog Window
//

void MainWindow::showOpenDialog()
{
    qDebug() << "[DEBUG] MainWindow.cpp - Open dialog triggered";
    QFileDialog dialog(this);
    QStringList filter;
    filter.append("All Files (*)");
    dialog.setDirectory(g_directoryManager->getDirectory());
    dialog.setNameFilters(filter);
    dialog.setWindowTitle("Open File");
    dialog.setWindowModality(Qt::ApplicationModal);
    connect(&dialog, &QFileDialog::fileSelected, g_directoryManager, &DirectoryManager::dirReceived);
    dialog.exec();
}

void MainWindow::showImage(std::shared_ptr<Image> image)
{
//    qDebug()<< centralWidget;
    centralWidget->showImage(image->getPixmap());
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

