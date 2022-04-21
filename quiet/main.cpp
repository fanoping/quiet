#include <QApplication>
#include "core/core.h"

#include "mainwindow.h"
#include "model/imagemanager.h"
#include "model/actionmanager.h"
#include "model/directorymanager.h"
#include "settings.h"
#include "object/node.h"


int main(int argc, char *argv[])
{
    Core core(argc, argv);

    core.show();

    return core.exec();
}
