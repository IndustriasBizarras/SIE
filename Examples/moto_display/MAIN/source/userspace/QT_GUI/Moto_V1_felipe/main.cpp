#include <QtGui/QApplication>
#include "moto.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Moto w;
    w.show();

    return a.exec();
}
