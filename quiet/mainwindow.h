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
#include "object/action.h"


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
     explicit MainWindow(QWidget *parent = 0);

    // Layout Settings
    std::shared_ptr<CentralWidget> centralWidget;

    /////////////////
    void initAttibutes();
    static void initConnect();
    void initLayout();

    // Menus
    std::unique_ptr<QMenu> m_fileMenu;
    std::unique_ptr<QMenu> m_contextMenu;

    // Build Menus
    void buildFileMenu();
    void buildContextMenu();
    void buildMenuBar();

    Action* buildSingleAction(const QString& actionName);

    // Actions
    // Storage of action objects
    QList<Action*> m_actionList; 

signals:

public slots:
    void showOpenDialog();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;

};

extern MainWindow* g_mainWindow;

#endif // MAINWINDOW_H
