#include "a10.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a10 w;
    w.show();
    return a.exec();
}
