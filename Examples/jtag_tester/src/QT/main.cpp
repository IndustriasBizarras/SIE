#include <QApplication>
 
#include "csv.h"
#include "stdio.h"
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    csv *dialog = new csv;

    QString csv, vcd, bit;
    for(int i=0; i< app.argc();i++){
    if(QString(app.argv()[i]).contains(".CSV", Qt::CaseInsensitive)==true) csv=QString(app.argv()[i]);
    else if(QString(app.argv()[i]).contains(".VCD", Qt::CaseInsensitive)==true) vcd=QString(app.argv()[i]);
    else if(QString(app.argv()[i]).contains(".BIT", Qt::CaseInsensitive)==true) bit=QString(app.argv()[i]);
    }

    dialog->get_dir(csv, vcd, bit);
    dialog->script();
    dialog->boundary_scan();
    dialog->pulsadores();

    dialog->show();
    return app.exec();
}
