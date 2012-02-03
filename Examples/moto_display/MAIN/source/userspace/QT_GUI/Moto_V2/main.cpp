#include <QtGui/QApplication>
#include "moto_v2.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    moto_v2 w;
    w.show();
    return a.exec();
}
