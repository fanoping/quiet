#include "mainwindow.h"


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


    // connect

//    actionManager->invokeAction("open");
//    actionManager->invokeAction("close");
//    imgLabel = new QLabel;
//    imgLabel->setBackgroundRole(QPalette::Base);
//    imgLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//    imgLabel->setScaledContents(true);

//    scrollArea = new QScrollArea;
//    scrollArea->setWidget(imgLabel);
//    setCentralWidget(scrollArea);


//    createMenus();

//    changeDir("C:/Users/sam18/Downloads/Img");

//    filters << "*.bmp";
//    currentDir.setNameFilters(filters);

//    setWindowTitle("QUIET v0.0.1");
//    resize(500, 500);
}

MainWindow::~MainWindow()
{


}







// private slots

void MainWindow::showOpenDialog()
{
    qDebug() << "open dialog triggered";
    QFileDialog dialog(this);
    QStringList filter;
    filter.append("All Files (*)");
    dialog.setDirectory("");
    dialog.setNameFilters(filter);
    dialog.setWindowTitle("Open File");
    dialog.setWindowModality(Qt::ApplicationModal);
//    connect(&dialog, &QFileDialog::fileSelected, this, &MainWindow::opened);
    dialog.exec();
}


// Protected Events

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::RightButton)  {
        qDebug() << "Right Button Pressed";
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
