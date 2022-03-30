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



void MainWindow::initConnect()
{
    qDebug()<<"connect";
    connect(actionManager, &ActionManager::openActionPublished, g_mainWindow, &MainWindow::showOpenDialog);
}



// private slots

void MainWindow::showOpenDialog()
{
    qDebug() << "[DEBUG] MainWindow.cpp - Open dialog triggered";
    QFileDialog dialog(this);
    QStringList filter;
    filter.append("All Files (*)");
    dialog.setDirectory("");
    dialog.setNameFilters(filter);
    dialog.setWindowTitle("Open File");
    dialog.setWindowModality(Qt::ApplicationModal);
    connect(&dialog, &QFileDialog::fileSelected, directoryManager, &DirectoryManager::dirReceived);
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

