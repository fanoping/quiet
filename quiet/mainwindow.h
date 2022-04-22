#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QtWidgets>
#include <QWidget>
#include <QDir>
#include <QHBoxLayout>
#include <QDebug>
#include <QPalette>
#include <QContextMenuEvent>


#include "view/centralwidget.h"
#include <memory>  //TODO: handle include memory

#include "model/directorymanager.h"
#include "model/actionmanager.h"
//#include "view/contextmenu.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // initialization
    static MainWindow* getInstance();
    ~MainWindow();

//    // initialize connection
//    static void initConnect();

    void changeDir(QString dir);



private:
     // constructor
     explicit MainWindow(QWidget *parent = 0);

    // Layout Settings
    QHBoxLayout layout;
    std::shared_ptr<CentralWidget> centralWidget;
//    std::unique_ptr<ContextMenu> contextMenu;

    QMenu* file;
    QMenu* contextMenu;
    /////////////////
    void initAttibutes();
    static void initConnect();
    void initLayout();


signals:

public slots:
    void showOpenDialog();


protected:
    void mousePressEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent* event) override;

};

extern MainWindow* g_mainWindow;

#endif // MAINWINDOW_H
