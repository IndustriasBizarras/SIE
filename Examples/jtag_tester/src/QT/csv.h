#ifndef MYQTAPP_H
#define MYQTAPP_H
 
#include "ui_csv.h"
#include "QThread"
#include "jz47xx_mmap.h"
#include "jz47xx_gpio.h"

#define CS2_PORT JZ_GPIO_PORT_B
#define CS2_PIN 26
 
class WidgetDisplay;

class csv : public QWidget, private Ui::find_inout
{
    Q_OBJECT
 
public:
    csv(QWidget *parent = 0);
 
public slots:
    void timerEvent(QTimerEvent*);
    JZ_REG *initFPGA_RAM();
    int bsdl_position(QString pin_number, QString status);
    QString pin_alias_status(QString signal);
    void script();
    void boundary_scan();
    void get_dir(QString csv, QString vcd, QString bit);
    void result_out();
    void pulsadores();

private:
    WidgetDisplay *miwidget;
    JZ_REG *RAM;
    QString dir_csv;
    QString dir_vcd;
    QString dir_bit;
    QStringList  registers;
    QStringList signals_name;
    QPixmap mipixmap;
    int photo;
    int cont_vi;
    int cont_hi;
    int cont2;
signals:
};
 
 
#endif
