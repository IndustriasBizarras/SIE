#include <QtGui/QApplication>
#include "text_test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    text_test w;
    w.show();

    return a.exec();
}
