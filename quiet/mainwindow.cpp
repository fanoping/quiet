#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    imgLabel = new QLabel;
    imgLabel->setBackgroundRole(QPalette::Base);
    imgLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imgLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setWidget(imgLabel);
    setCentralWidget(scrollArea);

    createActions();
    createMenus();

    changeDir("C:/Users/sam18/Downloads/Img");

    filters << "*.bmp";
    currentDir.setNameFilters(filters);

    setWindowTitle("QUIET v0.0.1");
    resize(500, 500);
}

MainWindow::~MainWindow()
{


}

void MainWindow::openDialog(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), currentDir.currentPath());
    fileInfo.setFile(fileName);
    changeDir(fileInfo.path());
    fileList = currentDir.entryList();

    fileNum = fileList.indexOf(fileInfo.fileName());
    qDebug() << fileNum;
    open(fileName);


}

void MainWindow::changeDir(QString dir)
{
    currentDir.setCurrent(dir);
    currentDir.setNameFilters(filters);
    fileNum = 0;
}

void MainWindow::open(QString fileName)
{
     setWindowTitle(fileInfo.fileName() + " - QUIET v0.0.1");

     QImage image(fileName);

     if (image.isNull()) {
         QMessageBox::information(this, tr("Image Viewer"), tr("Cannot load Image"));
     }
     imgLabel->setPixmap(QPixmap::fromImage(image));
     imgLabel->adjustSize();

}

void MainWindow::next()
{
    if (++fileNum>=fileList.length()){
        fileNum = 0;
    }
    QString fileName = currentDir.currentPath() + "/" + fileList.at(fileNum);
    fileInfo.setFile(fileName);
    open(fileName);
}

void MainWindow::prev()
{
    if (--fileNum< 0){
        fileNum = fileList.length() - 1;
    }
    QString fileName = currentDir.currentPath() + "/" + fileList.at(fileNum);
    fileInfo.setFile(fileName);
    open(fileName);
}


void MainWindow::createActions()
{
    openAction = new QAction(tr("Open..."), this);
    openAction->setShortcut(tr("Ctrl+O"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openDialog()));

    nextAction = new QAction(tr("Next"), this);
    nextAction->setShortcut(Qt::Key_Right);
    nextAction->setEnabled(true);
    connect(nextAction, SIGNAL(triggered()), this, SLOT(next()));

    prevAction = new QAction(tr("Next"), this);
    prevAction->setShortcut(Qt::Key_Left);
    prevAction->setEnabled(true);
    connect(prevAction, SIGNAL(triggered()), this, SLOT(prev()));
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(nextAction);
    fileMenu->addAction(prevAction);

    menuBar()->addMenu(fileMenu);
}

