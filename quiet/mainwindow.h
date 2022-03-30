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
#include "view/contextmenu.h"





class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* getInstance();

    ~MainWindow();

    void changeDir(QString dir);

    void initConnect();

private:
     explicit MainWindow(QWidget *parent = 0);



    void open(QString fileName);


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
    std::unique_ptr<ContextMenu> contextMenu;



signals:
    void onOpenAction(const QString&);
    void onOpenSelectedAction(const QString&);


//public slots:
//     void openDialog();
//     void next();
//     void prev();

public slots:
    void showOpenDialog();

protected:
    void mousePressEvent(QMouseEvent *event);

};

extern MainWindow* g_mainWindow;

#endif // MAINWINDOW_H
