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
}

MainWindow::~MainWindow()
{


}

MainWindow* MainWindow::getInstance()
{
    if(!g_mainWindow) {
        g_mainWindow = new MainWindow();
        initConnect();
        g_mainWindow = new MainWindow();
        qDebug() << g_mainWindow;

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
    qDebug() << sizeof(g_mainWindow);
    //ActionManager -> MainWindow (Received Action)
    connect(g_actionManager, &ActionManager::openActionPublished, g_mainWindow, &MainWindow::showOpenDialog);

//    connect(g_imageManager, &ImageManager::imageLoaded, g_mainWindow, &MainWindow::showImage);

    // private widget members connections

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
    filter << "*.bmp";
    dialog.setDirectory(g_directoryManager->getDirectory());
    dialog.setNameFilters(filter);
    dialog.setWindowTitle("Open File");
    dialog.setWindowModality(Qt::ApplicationModal);
    connect(&dialog, &QFileDialog::fileSelected, g_directoryManager, &DirectoryManager::dirReceived);
    dialog.exec();
}

//void MainWindow::showImage(std::shared_ptr<Image> image)
//{

//    qDebug()<<image.get();
//    centralWidget->showImage(image->getPixmap());
//}

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


