#ifndef CORE_H
#define CORE_H

#include <QObject>


#include "mainwindow.h"
#include "model/actionmanager.h"

/*

  Handles connection (signals and slots) between
  1. MainWindow - ActionManager
  2. MainWindow - DirectoryManager

*/


class Core : public QObject
{
    Q_OBJECT
public:
    Core();

    // Display function
    void show();

private:
    // initial functions
    void initUI();
    void initConnect();

    // UI mainwindow
    MainWindow* mw;


signals:

public slots:

};

#endif // CORE_H
