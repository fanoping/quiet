#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QtWidgets>
#include <QWidget>
#include <QDir>
#include <QHBoxLayout>


#include "view/centralwidget.h"
#include <memory>  //TODO: handle include memory

#include "model/directorymanager.h"
#include "model/actionmanager.h"


//namespace Ui {
//class MainWindow;
//}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void changeDir(QString dir);



private:
    void open(QString fileName);
    void createActions();
    void createMenus();


    QLabel* imgLabel;
    QScrollArea *scrollArea;

    QDir currentDir;
    int fileNum;
    QFileInfo fileInfo;

    QStringList fileList;
    QStringList filters;

    // Action
    QAction *openAction;
    QAction *nextAction;
    QAction *prevAction;


    // Menu
    QMenu * fileMenu;

    // Layout Settings
    QHBoxLayout layout;
    std::shared_ptr<CentralWidget> centralWidget;



    // Directory Manager
    DirectoryManager* directoryMgr;



//public slots:
//     void openDialog();
//     void next();
//     void prev();

private slots:
    void showOpenDialog();



};

#endif // MAINWINDOW_H
