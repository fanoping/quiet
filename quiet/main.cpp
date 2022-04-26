#include <QApplication>
#include "core/core.h"


int main(int argc, char *argv[])
{
    Core core(argc, argv);

    core.show();


    return core.exec();
}
