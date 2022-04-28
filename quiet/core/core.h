#ifndef CORE_H
#define CORE_H

//
// Wrapper of QApplication
// Maybe handle platform dependencies in the future
//

#include <QApplication>

#include "model/imagemanager.h"
#include "model/actionmanager.h"
#include "model/directorymanager.h"
#include "mainwindow.h"
#include "settings.h"


class Core: public QApplication
{
public:
    explicit Core(int &argc, char **argv);
    ~Core() override;

    void show();
};

#endif // CORE_H
